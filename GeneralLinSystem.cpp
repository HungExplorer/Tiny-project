#include "GeneralLinSystem.h"
#include <cassert>
#include <cmath>
GeneralLinSystem::GeneralLinSystem(const Matrix& A, const Vector& b)
    : mRows(A.Rows()), mCols(A.Cols())
{
    if (A.Rows() != b.getSize()) {
        throw std::invalid_argument("GeneralLinSystem: The number of rows in A must match the size of b.");
    }
    mpA = new Matrix(A);
    mpb = new Vector(b);
}
GeneralLinSystem::~GeneralLinSystem() {
    delete mpA;
    delete mpb;
}
int GeneralLinSystem::Rows() const {
    return mRows;
}
int GeneralLinSystem::Cols() const {
    return mCols;
}
Vector GeneralLinSystem::solvePseudoInverse() const {
    Matrix A_pinv = mpA->pseudoInverse();
    assert(A_pinv.Rows() == mCols && A_pinv.Cols() == mRows);
    Vector x(mCols);
    for (int i = 0; i < mCols; ++i) {
        double sum = 0.0;
        for (int j = 0; j < mRows; ++j) {
            sum += A_pinv(i + 1, j + 1) * (*mpb)[j];
        }
        x[i] = sum;
    }
    return x;
}
Vector GeneralLinSystem::solveTikhonov(double lambda) const {
    Matrix At = mpA->transpose();
    Matrix ATA = At * (*mpA);
    for (int i = 1; i <= mCols; ++i) {
        double cur = ATA(i, i);
        ATA(i, i) = cur + lambda;
    }
    Matrix invATA = ATA.inverse();
    Vector ATb(mCols);
    for (int i = 0; i < mCols; ++i) {
        double sum = 0.0;
        for (int j = 0; j < mRows; ++j) {
            sum += At(i + 1, j + 1) * (*mpb)[j];
        }
        ATb[i] = sum;
    }
    Vector x(mCols);
    for (int i = 0; i < mCols; ++i) {
        double sum = 0.0;
        for (int j = 0; j < mCols; ++j) {
            sum += invATA(i + 1, j + 1) * ATb[j];
        }
        x[i] = sum;
    }
    return x;
}
    return x;
}
