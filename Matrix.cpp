#include <iostream>
#include <cmath>
#include <stdexcept>
#include <cassert>
#include "Matrix.h"

using namespace std;

//Memory handling
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

//Constructor
Matrix::Matrix(int rows, int cols) : mNumRows(rows), mNumCols(cols) {
    if (rows <= 0 || cols <= 0)
        throw invalid_argument("Dimension must be positive");
    allocateMemory();
}

Matrix::Matrix(const Matrix& other) : mNumRows(other.mNumRows), mNumCols(other.mNumCols) {
    allocateMemory();
    for (int i = 0; i < mNumRows; ++i)
        for (int j = 0; j < mNumCols; ++j)
            mData[i][j] = other.mData[i][j];
}

//Assigning
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

//Deconstructor
Matrix::~Matrix() {
    freeMemory();
}

//Rows and Columns getter
int Matrix::Rows() const { return mNumRows; }
int Matrix::Cols() const { return mNumCols; }

//Getting value at index (i,j)
double& Matrix::operator()(int i, int j) {
    if (i < 0 || i >= mNumRows || j < 0 || j >= mNumCols)
        throw out_of_range("Out of bounds");
    return mData[i][j];
}

const double& Matrix::operator()(int i, int j) const {
    if (i < 0 || i >= mNumRows || j < 0 || j >= mNumCols)
        throw out_of_range("Out of bounds");
    return mData[i][j];
}

//Operation
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
        if (fabs(pivot) < 1e-12)
            throw runtime_error("Matrix is singular and can't be inverted");

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
        if (fabs(ATA.determinant()) < 1e-12)
            throw runtime_error("ATA is singular, pseudo-inverse undefined.");
        return ATA.inverse() * At;
    } else {
        Matrix At = transpose();
        Matrix AAT = (*this) * At;
        if (fabs(AAT.determinant()) < 1e-12)
            throw runtime_error("AAT is singular, pseudo-inverse undefined.");
        return At * AAT.inverse();
    }
}

//Data assignment
void Matrix::assign()
{
    cout << endl << "Enter the elements for matrix: " << endl;
    for (int i = 0; i < mNumRows; ++i)
    {
        for (int j = 0; j < mNumCols; ++j)
        {
            cout << "Enter the element at position: " << i+1 << " " << j+1 << ":";
            cin >> mData[i][j];
        }
    }
}

//Matrix display
void Matrix::display() const
{
    cout << "[";
    for (int i = 0; i < mNumRows; ++i)
    {
        if (i != 0)
        {
            cout << " ";
        }    
        for (int j = 0; j < mNumCols; ++j)
        {
            cout<< mData[i][j];
            if (j != mNumCols - 1)
            {
                cout << " ";
            }
            if (j == mNumCols - 1 && i != mNumRows - 1)
            {
                cout << endl;
            }
            if (j == mNumCols - 1 && i == mNumRows - 1)
            {
                cout << "]" << endl;
            }
        }
    }
}
