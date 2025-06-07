#ifndef GENERALLINSYSTEM_H
#define GENERALLINSYSTEM_H

#include "Matrix.h"
#include "Vector.h"
#include <stdexcept>

class GeneralLinSystem {
private:
    int mRows;
    int mCols;
    Matrix* mpA;
    Vector* mpb;

public:
    GeneralLinSystem(const Matrix& A, const Vector& b);
    ~GeneralLinSystem();

    int Rows() const;
    int Cols() const;

    Vector solvePseudoInverse() const;
    Vector solveTikhonov(double lambda) const;

    GeneralLinSystem(const GeneralLinSystem&) = delete;
    GeneralLinSystem& operator=(const GeneralLinSystem&) = delete;
};

#endif
