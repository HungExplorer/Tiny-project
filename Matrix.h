#ifndef MATRIX_H
#define MATRIX_H
#include <iostream>
#include <cassert>  
class Matrix {
private:
    int mNumRows, mNumCols;
    double** mData;
    void allocateMemory();
    void freeMemory();
public:
    Matrix(int rows, int cols);
    Matrix(const Matrix& other);
    Matrix& operator=(const Matrix& other);
    ~Matrix();
    int Rows() const;
    int Cols() const;
    double& operator()(int i, int j);
    const double& operator()(int i, int j) const;
    Matrix operator+(const Matrix& other) const;
    Matrix operator-(const Matrix& other) const;
    Matrix operator*(const Matrix& other) const;
    Matrix operator*(double scalar) const;
    Matrix transpose() const;
    double determinant() const;
    Matrix inverse() const;
    Matrix pseudoInverse() const;
    void manualAssign();
    void display() const; 
};
#endif
