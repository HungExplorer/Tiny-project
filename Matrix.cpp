// Matrix.cpp

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

// Constructor
Matrix::Matrix(int rows, int cols) 
    : mNumRows(rows), mNumCols(cols) 
{
    assert(rows > 0 && cols > 0);
    allocateMemory();
}

// Copy constructor
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

// Copy assignment
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

// Destructor
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
    // i, j phải là 1-based
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
            // Gán vào result(i+1, j+1) tương ứng
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
    // this là size (mNumRows x mNumCols), other là (other.mNumRows x other.mNumCols)
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
            // result có kích thước (mNumCols x mNumRows)
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
    // Tính định thức bằng phương pháp Laplace (recursive)
    for (int p = 1; p <= n; ++p) {
        // Tạo ma trận phụ có kích thước (n-1) x (n-1)
        Matrix sub(n - 1, n - 1);
        int subi = 1;  // chỉ số 1-based cho chính sub
        for (int i = 2; i <= n; ++i) {   // i lùi 1 để bỏ dòng đầu
            int subj = 1;
            for (int j = 1; j <= n; ++j) {
                if (j == p) continue;
                // Gán sub(subi, subj) = A(i,j)
                sub(subi, subj) = (*this)(i, j);
                subj++;
            }
            subi++;
        }
        // Tính hệ số (-1)^{1+p} * A(1,p) * det(sub)
        double sign = ( (p % 2) == 1 ) ? 1.0 : -1.0;
        det += sign * (*this)(1, p) * sub.determinant();
    }
    return det;
}

Matrix Matrix::inverse() const {
    assert(mNumRows == mNumCols);
    int n = mNumRows;

    // Tạo ma trận tăng cường kích thước n x (2n)
    Matrix aug(n, 2 * n);
    // Gán phần trái aug[1..n][1..n] = mData, và phải là I
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= n; ++j) {
            // mData là 0-based, nhưng operator() dùng 1-based
            aug(i, j) = (*this)(i, j);
            aug(i, j + n) = (i == j) ? 1.0 : 0.0;
        }
    }

    // Quá trình Gauss-Jordan để đưa aug về dạng [I | A^{-1}]
    for (int i = 1; i <= n; ++i) {
        double pivot = aug(i, i);
        assert(fabs(pivot) >= 1e-12);  
        // Chia cả hàng i cho pivot
        for (int j = 1; j <= 2 * n; ++j) {
            aug(i, j) /= pivot;
        }
        // Loại bỏ các phần tử không nằm trên đường chéo cột i
        for (int k = 1; k <= n; ++k) {
            if (k == i) continue;
            double factor = aug(k, i);
            for (int j = 1; j <= 2 * n; ++j) {
                aug(k, j) -= factor * aug(i, j);
            }
        }
    }

    // Bây giờ bên trái aug là I, bên phải aug là A^{-1}
    Matrix inv(n, n);
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= n; ++j) {
            inv(i, j) = aug(i, j + n);
        }
    }
    return inv;
}

Matrix Matrix::pseudoInverse() const {
    // Nếu ma trận vuông:  mNumRows == mNumCols, ta có thể dùng inverse như pseudo
    // Nhưng ta dùng công thức chung để cover over- và under-determined
    if (mNumRows >= mNumCols) {
        // A^+ = (A^T A)^{-1} A^T
        Matrix At = transpose();          // Kích thước (mNumCols x mNumRows)
        Matrix ATA = At * (*this);        // (mNumCols x mNumCols)
        // Phải đảo ATA
        assert(fabs(ATA.determinant()) >= 1e-12);
        Matrix invATA = ATA.inverse();    // (mNumCols x mNumCols)
        return invATA * At;               // Kết quả (mNumCols x mNumRows)
    } else {
        // A^+ = A^T (A A^T)^{-1}
        Matrix At = transpose();          // (mNumCols x mNumRows)
        Matrix AAT = (*this) * At;        // (mNumRows x mNumRows)
        assert(fabs(AAT.determinant()) >= 1e-12);
        Matrix invAAT = AAT.inverse();    // (mNumRows x mNumRows)
        return At * invAAT;               // (mNumCols x mNumRows)
    }
}

// Data assignment
void Matrix::manualAssign() {
    cout << endl << "Enter the elements for matrix: " << endl;
    for (int i = 1; i <= mNumRows; ++i) {
        for (int j = 1; j <= mNumCols; ++j) {
            cout << "Enter element (" << i << ", " << j << "): ";
            cin >> (*this)(i, j);
        }
    }
}

// Matrix display
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
            // Xuống dòng khi kết thúc mỗi hàng (ngoại trừ dòng cuối)
            if (j == mNumCols && i != mNumRows) {
                cout << endl;
            }
        }
        if (i == mNumRows) {
            cout << "]" << endl;
        }
    }
}
