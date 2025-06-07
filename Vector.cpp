#include "Vector.h"
#include <iostream>
#include <cassert> 
using namespace std;

Vector::Vector(int size) : mSize(size) {
    assert(size > 0);  
    mData = new double[mSize];
    for (int i = 0; i < mSize; ++i) {
        mData[i] = 0.0;
    }
}

Vector::Vector(const Vector& other) : mSize(other.mSize) {
    mData = new double[mSize];
    for (int i = 0; i < mSize; ++i) {
        mData[i] = other.mData[i];
    }
}

Vector::~Vector() {
    delete[] mData;
}

Vector& Vector::operator=(const Vector& other) {
    if (this != &other) {
        delete[] mData;
        mSize = other.mSize;
        mData = new double[mSize];
        for (int i = 0; i < mSize; ++i) {
            mData[i] = other.mData[i];
        }
    }
    return *this;
}

int Vector::getSize() const {
    return mSize;
}

double& Vector::operator[](int index) {
    assert(index >= 0 && index < mSize);
    return mData[index];
}

double& Vector::operator()(int index) {
    assert(index >= 1 && index <= mSize);
    return mData[index - 1];
}

Vector Vector::operator+(const Vector& other) const {
    assert(mSize == other.mSize);
    Vector result(mSize);
    for (int i = 0; i < mSize; ++i) {
        result.mData[i] = mData[i] + other.mData[i];
    }
    return result;
}

Vector Vector::operator-(const Vector& other) const {
    assert(mSize == other.mSize);
    Vector result(mSize);
    for (int i = 0; i < mSize; ++i) {
        result.mData[i] = mData[i] - other.mData[i];
    }
    return result;
}

double Vector::operator*(const Vector& other) const {
    assert(mSize == other.mSize);
    double result = 0.0;
    for (int i = 0; i < mSize; ++i) {
        result += mData[i] * other.mData[i];
    }
    return result;
}

Vector Vector::operator+(double value) const {
    Vector result(mSize);
    for (int i = 0; i < mSize; ++i) {
        result.mData[i] = mData[i] + value;
    }
    return result;
}

Vector Vector::operator-(double value) const {
    Vector result(mSize);
    for (int i = 0; i < mSize; ++i) {
        result.mData[i] = mData[i] - value;
    }
    return result;
}

Vector Vector::operator*(double value) const {
    Vector result(mSize);
    for (int i = 0; i < mSize; ++i) {
        result.mData[i] = mData[i] * value;
    }
    return result;
}

Vector Vector::operator-() const {
    Vector result(mSize);
    for (int i = 0; i < mSize; ++i) {
        result.mData[i] = -mData[i];
    }
    return result;
}

void Vector::manualAssign(){
    cout << endl << "Enter the elements for vector: " << endl;
    for (int i = 0; i < mSize; i++) 
    {
        cout << "Enter the value for position " << i+1 << ": ";
        cin >> mData[i];
    }
}

void Vector::assign(double* val) {
    assert(val != nullptr);
    for (int i = 0; i < mSize; i++)
    {
        mData[i] = val[i];
    }
}

void Vector::display() const{
    cout << endl << "[";
    for (int i = 0; i < mSize; i++) 
    {
        if(i != 0)
        {
            cout << " ";
        }
        cout << mData[i];
        if (i != mSize - 1)
            cout << endl;
        else 
            cout << "]" << endl;
    }
}
