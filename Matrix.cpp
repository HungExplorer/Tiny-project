#include "Matrix.h"
#include <cmath> 

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
Matrix::Matrix(int rows, int cols) : mNumRows(rows), mNumCols(cols) {
    assert(rows > 0 && cols > 0); 
    allocateMemory();
}

// Copy constructor
Matrix::Matrix(const Matrix& other) : mNumRows(other.mNumRows), mNumCols(other.mNumCols) {
    allocateMemory();
    for (int i = 0; i < mNumRows; ++i)
        for (int j = 0; j < mNumCols; ++j)
            mData[i][j] = other.mData[i][j];
}

// Copy assignment
Matrix& Matrix::operator=(const Matrix& other) {
    if (this == &other) return *this;
    freeMemory();
    mNumRows = other.mNumRows;
    mNumCols = other.mNumCols;
    allocateMemory();
    for (int i = 0; i < mNumRows; ++i)
        for (int j = 0; j < mNumCols; ++j)
            mData[i][j] = other.mData[i][j];
    return *this;
}

// Destructor
Matrix::~Matrix() {
    freeMemory();
}

int Matrix::Rows() const { return mNumRows; }
int Matrix::Cols() const { return mNumCols; }

double& Matrix::operator()(int i, int j) {
    assert(i >= 0 && i < mNumRows);
    assert(j >= 0 && j < mNumCols);
    return mData[i][j];
}

const double& Matrix::operator()(int i, int j) const {
    assert(i >= 0 && i < mNumRows);
    assert(j >= 0 && j < mNumCols);
    return mData[i][j];
}

Matrix Matrix::operator+(const Matrix& other) const {
    assert(mNumRows == other.mNumRows && mNumCols == other.mNumCols);
    Matrix result(mNumRows, mNumCols);
    for (int i = 0; i < mNumRows; ++i)
        for (int j = 0; j < mNumCols; ++j)
            result(i, j) = mData[i][j] + other.mData[i][j];
    return result;
}

Matrix Matrix::operator-(const Matrix& other) const {
    assert(mNumRows == other.mNumRows && mNumCols == other.mNumCols);
    Matrix result(mNumRows, mNumCols);
    for (int i = 0; i < mNumRows; ++i)
        for (int j = 0; j < mNumCols; ++j)
            result(i, j) = mData[i][j] - other.mData[i][j];
    return result;
}

Matrix Matrix::operator*(const Matrix& other) const {
    assert(mNumCols == other.mNumRows);
    Matrix result(mNumRows, other.mNumCols);
    for (int i = 0; i < mNumRows; ++i)
        for (int j = 0; j < other.mNumCols; ++j)
            for (int k = 0; k < mNumCols; ++k)
                result(i, j) += mData[i][k] * other.mData[k][j];
    return result;
}

Matrix Matrix::operator*(double scalar) const {
    Matrix result(mNumRows, mNumCols);
    for (int i = 0; i < mNumRows; ++i)
        for (int j = 0; j < mNumCols; ++j)
            result(i, j) = mData[i][j] * scalar;
    return result;
}

Matrix Matrix::transpose() const {
    Matrix result(mNumCols, mNumRows);
    for (int i = 0; i < mNumRows; ++i)
        for (int j = 0; j < mNumCols; ++j)
            result(j, i) = mData[i][j];
    return result;
}

double Matrix::determinant() const {
    assert(mNumRows == mNumCols);
    if (mNumRows == 1) return mData[0][0];
    if (mNumRows == 2) return mData[0][0] * mData[1][1] - mData[0][1] * mData[1][0];

    double det = 0;
    for (int p = 0; p < mNumCols; ++p) {
        Matrix sub(mNumRows - 1, mNumCols - 1);
        for (int i = 1; i < mNumRows; ++i) {
            int colIdx = 0;
            for (int j = 0; j < mNumCols; ++j) {
                if (j == p) continue;
                sub(i - 1, colIdx++) = mData[i][j];
            }
        }
        det += (p % 2 == 0 ? 1 : -1) * mData[0][p] * sub.determinant();
    }
    return det;
}

Matrix Matrix::inverse() const {
    assert(mNumRows == mNumCols);
    int n = mNumRows;
    Matrix aug(n, 2 * n);

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            aug(i, j) = mData[i][j];
            aug(i, j + n) = (i == j) ? 1.0 : 0.0;
        }
    }

    for (int i = 0; i < n; ++i) {
        double pivot = aug(i, i);
        assert(fabs(pivot) >= 1e-12); // thay cho throw lỗi singular

        for (int j = 0; j < 2 * n; ++j)
            aug(i, j) /= pivot;

        for (int k = 0; k < n; ++k) {
            if (k == i) continue;
            double factor = aug(k, i);
            for (int j = 0; j < 2 * n; ++j)
                aug(k, j) -= factor * aug(i, j);
        }
    }

    Matrix inv(n, n);
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j)
            inv(i, j) = aug(i, j + n);

    return inv;
}

Matrix Matrix::pseudoInverse() const {
    if (mNumRows >= mNumCols) {
        Matrix At = transpose();
        Matrix ATA = At * (*this);
        assert(fabs(ATA.determinant()) >= 1e-12);
        return ATA.inverse() * At;
    } else {
        Matrix At = transpose();
        Matrix AAT = (*this) * At;
        assert(fabs(AAT.determinant()) >= 1e-12);
        return At * AAT.inverse();
    }
}
