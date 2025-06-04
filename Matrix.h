#ifndef MATRIX_H
#define MATRIX_H

#include <iostream>
#include <stdexcept>

class Matrix {
private:
    int mNumRows, mNumCols;
    double** mData;

    void allocateMemory();
    void freeMemory();

public:
//Constructor and Destructor
    Matrix(int rows, int cols);
    Matrix(const Matrix& other);
    Matrix& operator=(const Matrix& other);
    ~Matrix();
//Accessors
    int Rows() const;
    int Cols() const;
//Overload bracket for element access
    double& operator()(int i, int j);
    const double& operator()(int i, int j) const;
//Addition, Subtraction, Multiplication and Scalar
    Matrix operator+(const Matrix& other) const;
    Matrix operator-(const Matrix& other) const;
    Matrix operator*(const Matrix& other) const;
    Matrix operator*(double scalar) const;
//Determinant, Inverse and psuedoInverse of Matrix
    Matrix transpose() const;
    double determinant() const;
    Matrix inverse() const;
    Matrix pseudoInverse() const;

};

#endif 
