// main_regression.cpp

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <cstdlib>   // srand, rand
#include <ctime>     // time
#include <cmath>
#include <iomanip>

#include "Matrix.h"
#include "Vector.h"
#include "GeneralLinSystem.h"

using namespace std;

/**
 * Đọc dữ liệu từ file "machine.data" (CSV) và lưu vào hai vector:
 *   - dataX: vector<vector<double>> kích thước = (209) x 6, chứa 6 đặc trưng số (MYCT..CHMAX)
 *   - dataY: vector<double> kích thước = 209, chứa PRP (mục tiêu)
 *
 * Trả về true nếu đọc thành công, false nếu có lỗi (không mở được file).
 */
bool loadData(const string& filename,
              vector< vector<double> >& dataX,
              vector<double>& dataY)
{
    ifstream fin(filename);
    if (!fin.is_open()) {
        cerr << "Không thể mở file " << filename << endl;
        return false;
    }

    string line;
    // Không có dòng header, dữ liệu bắt đầu ngay từ dòng đầu.
    while (getline(fin, line)) {
        if (line.empty()) continue;
        // Dùng stringstream để tách theo dấu phẩy
        stringstream ss(line);
        vector<string> tokens;
        string token;
        while (getline(ss, token, ',')) {
            tokens.push_back(token);
        }
        // Mỗi dòng phải có đúng 10 trường
        if (tokens.size() != 10) {
            cerr << "Dữ liệu sai định dạng, dòng: " << line << endl;
            continue;
        }
        // Chuyển 6 trường số (tokens[2]..tokens[7]) thành double
        vector<double> features(6);
        for (int i = 0; i < 6; ++i) {
            features[i] = atof(tokens[2 + i].c_str());
        }
        // PRP ở tokens[8]
        double prp = atof(tokens[8].c_str());

        dataX.push_back(features);
        dataY.push_back(prp);
    }

    fin.close();
    return true;
}

/**
 * Chia ngẫu nhiên chỉ số [0..N-1] thành training và testing.
 *   - N: tổng số hàng
 *   - trainIdx: vector<int> lưu chỉ số của training (size ≈ 0.8*N)
 *   - testIdx:  vector<int> lưu chỉ số của testing (size ≈ 0.2*N)
 */
void trainTestSplit(int N,
                    vector<int>& trainIdx,
                    vector<int>& testIdx,
                    double trainFraction = 0.8,
                    unsigned int randomSeed = 12345)
{
    vector<int> indices(N);
    for (int i = 0; i < N; ++i) indices[i] = i;

    srand(randomSeed);
    // Hoán vị ngẫu nhiên
    for (int i = N - 1; i > 0; --i) {
        int j = rand() % (i + 1);
        swap(indices[i], indices[j]);
    }

    int nTrain = static_cast<int>(floor(trainFraction * N));
    trainIdx.assign(indices.begin(), indices.begin() + nTrain);
    testIdx.assign(indices.begin() + nTrain, indices.end());
}

/**
 * Tính RMSE:
 *   - yTrue: vector<double> độ dài M
 *   - yPred: vector<double> độ dài M
 * Trả về sqrt( (1/M) * sum (yTrue[i] - yPred[i])^2 ).
 */
double computeRMSE(const vector<double>& yTrue,
                   const vector<double>& yPred)
{
    int M = static_cast<int>(yTrue.size());
    if (M == 0 || static_cast<int>(yPred.size()) != M) return -1.0;

    double sse = 0.0;
    for (int i = 0; i < M; ++i) {
        double diff = yTrue[i] - yPred[i];
        sse += diff * diff;
    }
    return sqrt(sse / M);
}

int main()
{
    cout << fixed << setprecision(4);

    // 1) Đọc dữ liệu
    vector< vector<double> > dataX; // mỗi phần tử là vector độ dài 6
    vector<double> dataY;           // mỗi phần tử là PRP

    if (!loadData("machine.data", dataX, dataY)) {
        return 1; // lỗi mở file
    }

    int N = static_cast<int>(dataX.size()); // N phải là 209
    cout << "Đã đọc tổng cộng " << N << " dòng dữ liệu.\n";

    // 2) Chia train/test (80/20)
    vector<int> trainIdx, testIdx;
    trainTestSplit(N, trainIdx, testIdx, 0.8, 2025 /*seed*/);

    int nTrain = static_cast<int>(trainIdx.size());
    int nTest  = static_cast<int>(testIdx.size());
    cout << " Tập training: " << nTrain << " dòng,\n"
         << " Tập testing : " << nTest  << " dòng.\n\n";

    // 3) Tạo ma trận X_train (nTrain x 6) và vector y_train (nTrain)
    Matrix X_train(nTrain, 6);
    Vector y_train(nTrain);
    for (int ii = 0; ii < nTrain; ++ii) {
        int idx = trainIdx[ii];
        for (int j = 0; j < 6; ++j) {
            // X_train(ii+1, j+1) = dataX[idx][j]
            X_train(ii + 1, j + 1) = dataX[idx][j];
        }
        y_train(ii + 1) = dataY[idx];
    }

    // 4) Tính hệ (X^T X) * w = X^T * y  (6x6 hệ) → w là Vector độ dài 6
    //    Ví dụ thế này sẽ tránh gọi pseudoInverse trực tiếp (dùng GeneralLinSystem)
    Matrix Xt = X_train.transpose();        // (6 x nTrain)
    Matrix XtX = Xt * X_train;              // (6 x 6)
    // Tạo vector X^T * y (6x1)
    Vector Xty(6);
    for (int i = 1; i <= 6; ++i) {
        double sum = 0.0;
        for (int k = 1; k <= nTrain; ++k) {
            sum += Xt(i, k) * y_train(k);
        }
        Xty(i) = sum;
    }

    // Dùng GeneralLinSystem để giải XtX * w = Xty
    GeneralLinSystem gs(XtX, Xty);
    Vector w = gs.solvePseudoInverse(); 
    // Lưu ý: solvePseudoInverse() (nếu dùng ma trận không vuông) 
    //   thì ta phải gọi solvePseudoInverse() riêng. Nhưng XtX ở đây vuông (6x6),
    //   do đó ta nên gọi solve() (Gaussian). Tuy nhiên solve() yêu cầu ma trận vuông 
    //   và không phải Positive‐Definite luôn, nhưng XtX là chéo dương nên solve() ok.

    // Vì GeneralLinSystem.solvePseudoInverse() giả định A m×n → w có chiều n
    // Trường hợp XtX là 6×6 (vuông), solvePseudoInverse() cũng tự động chuyển sang (ATA)^{-1} A^T,
    // nhưng để an toàn, bạn cũng có thể dùng trực tiếp solve() cho hệ vuông:
    // Vector w = GeneralLinSystem(XtX, Xty).solve();

    cout << "Hệ số hồi quy w (6 phần tử):\n";
    w.display();  // In w[1..6]

    // 5) Dự đoán trên tập training, tính RMSE_train
    vector<double> yTrainTrue(nTrain), yTrainPred(nTrain);
    for (int ii = 0; ii < nTrain; ++ii) {
        int idx = trainIdx[ii];
        double yTrue = dataY[idx];
        double yPred = 0.0;
        for (int j = 0; j < 6; ++j) {
            yPred += w[j] * dataX[idx][j];
        }
        yTrainTrue[ii] = yTrue;
        yTrainPred[ii] = yPred;
    }
    double rmseTrain = computeRMSE(yTrainTrue, yTrainPred);

    // 6) Dự đoán trên tập testing, tính RMSE_test
    vector<double> yTestTrue(nTest), yTestPred(nTest);
    for (int ii = 0; ii < nTest; ++ii) {
        int idx = testIdx[ii];
        double yTrue = dataY[idx];
        double yPred = 0.0;
        for (int j = 0; j < 6; ++j) {
            yPred += w[j] * dataX[idx][j];
        }
        yTestTrue[ii] = yTrue;
        yTestPred[ii] = yPred;
    }
    double rmseTest = computeRMSE(yTestTrue, yTestPred);

    cout << "\nRMSE trên tập training: " << rmseTrain << "\n";
    cout << "RMSE trên tập testing : " << rmseTest  << "\n";

    return 0;
}
