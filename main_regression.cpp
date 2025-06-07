#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include <iomanip>
#include "Matrix.h"
#include "Vector.h"
#include "GeneralLinSystem.h"
using namespace std;
bool loadData(const string& filename,
              vector< vector<double> >& dataX,
              vector<double>& dataY)
{
    ifstream fin(filename);
    if (!fin.is_open()) {
        cerr << "Cannot open file " << filename << endl;
        return false;
    }
    string line;
    while (getline(fin, line)) {
        if (line.empty()) continue;
        stringstream ss(line);
        vector<string> tokens;
        string token;
        while (getline(ss, token, ',')) {
            tokens.push_back(token);
        }
        if (tokens.size() != 10) {
            cerr << "Invalid data format, line: " << line << endl;
            continue;
        }
        vector<double> features(6);
        for (int i = 0; i < 6; ++i) {
            features[i] = atof(tokens[2 + i].c_str());
        }
        double prp = atof(tokens[8].c_str());

        dataX.push_back(features);
        dataY.push_back(prp);
    }

    fin.close();
    return true;
}

void trainTestSplit(int N,
                    vector<int>& trainIdx,
                    vector<int>& testIdx,
                    double trainFraction = 0.8,
                    unsigned int randomSeed = 12345)
{
    vector<int> indices(N);
    for (int i = 0; i < N; ++i) indices[i] = i;

    srand(randomSeed);
    for (int i = N - 1; i > 0; --i) {
        int j = rand() % (i + 1);
        swap(indices[i], indices[j]);
    }

    int nTrain = static_cast<int>(floor(trainFraction * N));
    trainIdx.assign(indices.begin(), indices.begin() + nTrain);
    testIdx.assign(indices.begin() + nTrain, indices.end());
}

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

    vector< vector<double> > dataX;
    vector<double> dataY;

    if (!loadData("machine.data", dataX, dataY)) {
        return 1;
    }

    int N = static_cast<int>(dataX.size());
    cout << "Read total " << N << " rows of data.\n";

    vector<int> trainIdx, testIdx;
    trainTestSplit(N, trainIdx, testIdx, 0.8, 2025);

    int nTrain = static_cast<int>(trainIdx.size());
    int nTest  = static_cast<int>(testIdx.size());
    cout << " Training set: " << nTrain << " rows,\n"
         << " Testing set : " << nTest  << " rows.\n\n";

    Matrix X_train(nTrain, 6);
    Vector y_train(nTrain);
    for (int ii = 0; ii < nTrain; ++ii) {
        int idx = trainIdx[ii];
        for (int j = 0; j < 6; ++j) {
            X_train(ii + 1, j + 1) = dataX[idx][j];
        }
        y_train(ii + 1) = dataY[idx];
    }

    Matrix Xt = X_train.transpose();
    Matrix XtX = Xt * X_train;
    Vector Xty(6);
    for (int i = 1; i <= 6; ++i) {
        double sum = 0.0;
        for (int k = 1; k <= nTrain; ++k) {
            sum += Xt(i, k) * y_train(k);
        }
        Xty(i) = sum;
    }

    GeneralLinSystem gs(XtX, Xty);
    Vector w = gs.solvePseudoInverse();

    cout << "Regression coefficients w (6 elements):\n";
    w.display();

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

    cout << "\nRMSE on training set: " << rmseTrain << "\n";
    cout << "RMSE on testing set : " << rmseTest  << "\n";

    return 0;
}
