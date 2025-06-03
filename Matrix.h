#ifndef MATRIX_H
#define MATRIX_H

#include <iostream>
#include <stdexcept>
#include <cassert>

class Matrix {
private:
    int mNumRows;
    int mNumCols;
    double** mData;
    
    void allocateMemory();
    void freeMemory();
    void copyFrom(const Matrix& other);

public:
    Matrix(int rows, int cols);
    Matrix(const Matrix& other);
    ~Matrix();
    
    int rows() const { return mNumRows; }
    int cols() const { return mNumCols; }
    
    double& operator()(int i, int j);
    const double& operator()(int i, int j) const;
    
    Matrix& operator=(const Matrix& other);
    
    Matrix operator+() const;
    Matrix operator-() const;
    
    Matrix operator+(const Matrix& other) const;
    Matrix operator-(const Matrix& other) const;
    Matrix operator*(const Matrix& other) const;
    Matrix operator*(double scalar) const;
    friend Matrix operator*(double scalar, const Matrix& mat);
    
    Vector operator*(const Vector& vec) const;
    
    double determinant() const;
    Matrix inverse() const;
    Matrix transpose() const;
    Matrix pseudoInverse() const;
};

#endif