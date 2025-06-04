#ifndef MATRIX_H
#define MATRIX_H

#include <iostream>
#include <stdexcept>

class Matrix {
private:
    int mNumRows, mNumCols;
    double** mData;

    //Memory Handling
    void allocateMemory();
    void freeMemory();

public:
    //Instructor
    Matrix(int rows, int cols);

    //Instructor with other object
    Matrix(const Matrix& other);

    //Assigning
    Matrix& operator=(const Matrix& other);

    //Deconstructor
    ~Matrix();

    //Rows and Columns 
    int Rows() const;
    int Cols() const;

    //Getting value at index (i,j)
    double& operator()(int i, int j);
    const double& operator()(int i, int j) const;

    //Operation
    //Addition
    Matrix operator+(const Matrix& other) const;

    //Subtraction
    Matrix operator-(const Matrix& other) const;

    //Multiplication
    Matrix operator*(const Matrix& other) const;

    //Scalar multiplication
    Matrix operator*(double scalar) const;

    //Transpose
    Matrix transpose() const;

    //Determinant
    double determinant() const;

    //Invert
    Matrix inverse() const;

    //pseudoInverse
    Matrix pseudoInverse() const;

    //Data assignment
    void assign();

    //Matrix display
    void display() const;
};

#endif 
