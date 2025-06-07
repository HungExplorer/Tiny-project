#include "Matrix.h"
#include <iostream>
#include <cmath> 
#include <cassert>
using namespace std;
void Matrix::allocateMemory() {
    mData = new double*[mNumRows];
    for (int i = 0; i < mNumRows; ++i) {
        mData[i] = new double[mNumCols]();
    }
}
void Matrix::freeMemory() {
    for (int i = 0; i < mNumRows; ++i) {
        delete[] mData[i];
    }
    delete[] mData;
}
Matrix::Matrix(int rows, int cols) 
    : mNumRows(rows), mNumCols(cols) 
{
    assert(rows > 0 && cols > 0);
    allocateMemory();
}
Matrix::Matrix(const Matrix& other) 
    : mNumRows(other.mNumRows), mNumCols(other.mNumCols) 
{
    allocateMemory();
    for (int i = 0; i < mNumRows; ++i) {
        for (int j = 0; j < mNumCols; ++j) {
            mData[i][j] = other.mData[i][j];
        }
    }
}
Matrix& Matrix::operator=(const Matrix& other) {
    if (this == &other) return *this;
    freeMemory();
    mNumRows = other.mNumRows;
    mNumCols = other.mNumCols;
    allocateMemory();
    for (int i = 0; i < mNumRows; ++i) {
        for (int j = 0; j < mNumCols; ++j) {
            mData[i][j] = other.mData[i][j];
        }
    }
    return *this;
}
Matrix::~Matrix() {
    freeMemory();
}

int Matrix::Rows() const { 
    return mNumRows; 
}
int Matrix::Cols() const { 
    return mNumCols; 
}
double& Matrix::operator()(int i, int j) {
    assert(i >= 1 && i <= mNumRows);
    assert(j >= 1 && j <= mNumCols);
    return mData[i - 1][j - 1];
}
const double& Matrix::operator()(int i, int j) const {
    assert(i >= 1 && i <= mNumRows);
    assert(j >= 1 && j <= mNumCols);
    return mData[i - 1][j - 1];
}
Matrix Matrix::operator+(const Matrix& other) const {
    assert(mNumRows == other.mNumRows && mNumCols == other.mNumCols);
    Matrix result(mNumRows, mNumCols);
    for (int i = 0; i < mNumRows; ++i) {
        for (int j = 0; j < mNumCols; ++j) {
            result(i + 1, j + 1) = mData[i][j] + other.mData[i][j];
        }
    }
    return result;
}
Matrix Matrix::operator-(const Matrix& other) const {
    assert(mNumRows == other.mNumRows && mNumCols == other.mNumCols);
    Matrix result(mNumRows, mNumCols);
    for (int i = 0; i < mNumRows; ++i) {
        for (int j = 0; j < mNumCols; ++j) {
            result(i + 1, j + 1) = mData[i][j] - other.mData[i][j];
        }
    }
    return result;
}
Matrix Matrix::operator*(const Matrix& other) const {
    assert(mNumCols == other.mNumRows);
    Matrix result(mNumRows, other.mNumCols);
    for (int i = 0; i < mNumRows; ++i) {
        for (int j = 0; j < other.mNumCols; ++j) {
            double sum = 0.0;
            for (int k = 0; k < mNumCols; ++k) {
                sum += mData[i][k] * other.mData[k][j];
            }
            result(i + 1, j + 1) = sum;
        }
    }
    return result;
}
Matrix Matrix::operator*(double scalar) const {
    Matrix result(mNumRows, mNumCols);
    for (int i = 0; i < mNumRows; ++i) {
        for (int j = 0; j < mNumCols; ++j) {
            result(i + 1, j + 1) = mData[i][j] * scalar;
        }
    }
    return result;
}
Matrix Matrix::transpose() const {
    Matrix result(mNumCols, mNumRows);
    for (int i = 0; i < mNumRows; ++i) {
        for (int j = 0; j < mNumCols; ++j) {
            result(j + 1, i + 1) = mData[i][j];
        }
    }
    return result;
}
double Matrix::determinant() const {
    assert(mNumRows == mNumCols);
    int n = mNumRows;
    if (n == 1) {
        return mData[0][0];
    }
    if (n == 2) {
        return mData[0][0] * mData[1][1] - mData[0][1] * mData[1][0];
    }
    double det = 0.0;
    for (int p = 1; p <= n; ++p) {
        Matrix sub(n - 1, n - 1);
        int subi = 1;  
        for (int i = 2; i <= n; ++i) {   
            int subj = 1;
            for (int j = 1; j <= n; ++j) {
                if (j == p) continue;
                sub(subi, subj) = (*this)(i, j);
                subj++;
            }
            subi++;
        }
        double sign = ( (p % 2) == 1 ) ? 1.0 : -1.0;
        det += sign * (*this)(1, p) * sub.determinant();
    }
    return det;
}
Matrix Matrix::inverse() const {
    assert(mNumRows == mNumCols);
    int n = mNumRows;
    Matrix aug(n, 2 * n);
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= n; ++j) {
            aug(i, j) = (*this)(i, j);
            aug(i, j + n) = (i == j) ? 1.0 : 0.0;
        }
    }
    for (int i = 1; i <= n; ++i) {
        double pivot = aug(i, i);
        assert(fabs(pivot) >= 1e-12);  
        for (int j = 1; j <= 2 * n; ++j) {
            aug(i, j) /= pivot;
        }
        for (int k = 1; k <= n; ++k) {
            if (k == i) continue;
            double factor = aug(k, i);
            for (int j = 1; j <= 2 * n; ++j) {
                aug(k, j) -= factor * aug(i, j);
            }
        }
    }
    Matrix inv(n, n);
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= n; ++j) {
            inv(i, j) = aug(i, j + n);
        }
    }
    return inv;
}
Matrix Matrix::pseudoInverse() const {
    if (mNumRows >= mNumCols) {
        Matrix At = transpose();         
        Matrix ATA = At * (*this);       
        assert(fabs(ATA.determinant()) >= 1e-12);
        Matrix invATA = ATA.inverse();   
        return invATA * At;               
    } else {
        Matrix At = transpose();          
        Matrix AAT = (*this) * At;        
        assert(fabs(AAT.determinant()) >= 1e-12);
        Matrix invAAT = AAT.inverse();    
        return At * invAAT;             
    }
}
void Matrix::manualAssign() {
    cout << endl << "Enter the elements for matrix: " << endl;
    for (int i = 1; i <= mNumRows; ++i) {
        for (int j = 1; j <= mNumCols; ++j) {
            cout << "Enter element (" << i << ", " << j << "): ";
            cin >> (*this)(i, j);
        }
    }
}
void Matrix::display() const {
    cout << endl << "[";
    for (int i = 1; i <= mNumRows; ++i) {
        if (i != 1) {
            cout << " ";
        }
        for (int j = 1; j <= mNumCols; ++j) {
            cout << (*this)(i, j);
            if (j != mNumCols) {
                cout << " ";
            }
            if (j == mNumCols && i != mNumRows) {
                cout << endl;
            }
        }
        if (i == mNumRows) {
            cout << "]" << endl;
        }
    }
}
