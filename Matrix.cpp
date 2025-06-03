#include <iostream>
#include <cmath>
#include <cassert>
#include <stdexcept>
#include <vector>

using namespace std;

class Matrix {
private:
    int mNumRows;
    int mNumCols;
    double** mData;
    void allocateMemory(){
        mData = new double*[mNumRows];
        for (int i = 0; i < mNumRows; i++) {
            mData[i] = new double[mNumCols];
            }
    }
    void freeMemory(){
        for (int i = 0; i < mNumRows; ++i) {
            delete[] mData[i];
        }
        delete[] mData;
    }
public:
    Matrix(int Rows, int Cols) {
        mNumRows = Rows;
        mNumCols = Cols;
        if (Rows <= 0 || Cols <= 0)
        {
           throw invalid_argument("Must be positive");
        }
        allocateMemory();
        }
    Matrix(const Matrix& other) {
        mNumCols = other.mNumCols;
        mNumRows = other.mNumRows;
        allocateMemory();
        }
    ~Matrix() {
        freeMemory();
    }
    int Rows() const { return mNumRows; }
    int Cols() const { return mNumCols; }
    int operator()(int i, int j){
        if (i < 1 || i > mNumRows || j < 1 || j > mNumCols) {
            throw out_of_range("Matrix invalid");
        }
        return mData [i - 1] [j - 1];
    }
    const double& operator()(int i, int j) const {
        if (i < 1 || i > mNumRows || j < 1 || j > mNumCols) {
            throw out_of_range("Matrix indices out of range");
        }
        return mData[i - 1][j - 1];
    }
    Matrix operator+() const{
    return *this;
    }
    Matrix operator-() const{
        Matrix result(mNumRows, mNumCols);
        for (int i = 0; i < mNumRows; i++) {
            for (int j = 0; j < mNumCols; j++) {
                result.mData[i][j] = -mData[i][j];
            }
        }
        return result;
    }
    Matrix operator+(const Matrix& other) const{
        assert(mNumRows == other.mNumRows && mNumCols == other.mNumCols);
        Matrix result(mNumRows, mNumCols);
        for (size_t i = 1; i <= mNumRows; ++i) {
            for (size_t j = 1; j <= mNumCols; ++j) {
                result.mData[i][j] = mData[i][j] + other.mData[i][j];
            }
        }
        return result;
    }
    Matrix operator-(const Matrix& other) const{
        assert(mNumRows == other.mNumRows && mNumCols == other.mNumCols);
        Matrix result(mNumRows, mNumCols);
        for (int i = 0; i < mNumRows; i++) {
            for (int j = 0; j < mNumCols; j++) {
                result.mData[i][j] = mData[i][j] - other.mData[i][j];
            }
        }
        return result;
    }
    Matrix operator*(const Matrix& other) const {
        assert(mNumCols == other.mNumRows);
        Matrix result(mNumRows, other.mNumCols);
        for (int i = 0; i < mNumRows; i++) {
            for (int j = 0; j < other.mNumCols; j++) {
                for (int k = 0; k < mNumCols; k++) {
                    result.mData[i][j] += mData[i][k] * other.mData[k][j];
                }
            }
        }
        return result;
    }
    Matrix operator*(double scalar) const {
        Matrix result(mNumRows, mNumCols);
        for (int i = 0; i < mNumRows; i++) {
            for (int j = 0; j < mNumCols; j++) {
                result.mData[i][j] = mData[i][j] * scalar;
            }
        }
        return result;
    }
    friend class Vector;
    Vector operator*(const Vector& vec) const {
        assert(mNumCols == vec.size());
        Vector result(mNumRows);
        for (int i = 0; i < mNumRows; i++) {
            for (int j = 0; j < mNumCols; j++) {
                result[i] += mData[i][j] * vec[j];
            }
        }
        return result;
    }
    double determinantOfMatrix() const {
        assert(mNumCols == mNumRows);
        if (mNumRows == 1) return mData[0][0];
        if (mNumRows == 2)
            return mData[0][0] * mData[1][1] - mData[0][1] * mData[1][0];
        double det = 0.0;
        for (int p = 0; p < mNumCols; ++p) {
            Matrix sub(mNumRows - 1, mNumCols - 1);
            for (int i = 1; i < mNumRows; ++i)
                for (int j = 0, col = 0; j < mNumCols; ++j) {
                    if (j == p) continue;
                    sub.mData[i - 1][col++] = mData[i][j];
                }
            det += (p % 2 == 0 ? 1 : -1) * mData[0][p] * sub.determinantOfMatrix();
        }
        return det;
    }
    Matrix Inverse() const {
        float temp;
        int order = mNumRows;
        assert(mNumCols == mNumRows);
        Matrix aug(order, 2*order);
        for (int i = 0; i < order; ++i) {
            for (int j = 0; j < order; ++j) {
                aug.mData[i][j] = mData[i][j];
            }
        }
        for (int i = 0; i < order; ++i) {
            for (int j = 0; j < 2 * order; ++j) {
                if (j == (i + order)) {
                    aug.mData[i][j] = 1;
                }
            }
        }
        for (int i = order - 1; i > 0; i--) {
            if (aug.mData[i - 1][0] < aug.mData[i][0]) {
                double* temp = aug.mData[i];
                aug.mData[i] = aug.mData[i - 1];
                aug.mData[i - 1] = temp;
            }
        }
        double temp;
        for (int i = 0; i < order; i++) {
            for (int j = 0; j < order; j++) {
                if (j != i) {
                    temp = aug.mData[j][i] / aug.mData[i][i];
                    for (int k = 0; k < 2 * order; k++) {
                        aug.mData[j][k] -= aug.mData[i][k] * temp;
                    }
                }
            }
        }
        for (int i = 0; i < order; i++) {
            temp = aug.mData[i][i];
            for (int j = 0; j < 2 * order; j++) {
                aug.mData[i][j] = aug.mData[i][j] / temp;
            }
        }
        Matrix inverse(order, order);
        for (int i = 0; i < order; ++i) {
            for (int j = 0; j < order; ++j) {
                inverse.mData[i][j] = aug.mData[i][j + order];
            }
        }
    
        return inverse;
    }
    Matrix transpose() const {
        Matrix result(mNumCols, mNumRows);
        for (size_t i = 0; i < mNumRows; ++i) {
            for (size_t j = 0; j < mNumCols; ++j) {
                result(i, j) = mData[i][j];  
            }
        }
        return result;
    }
    Matrix pseudoInverse() const {
        if (mNumRows >= mNumCols) {
            Matrix ATA = transpose() * (*this);
            Matrix ATA_inv = ATA.Inverse();
            return ATA_inv * transpose();
        } else {
            Matrix AAT = (*this) * transpose();
            Matrix AAT_inv = AAT.Inverse();
            return transpose() * AAT_inv;
        }
    }
};
