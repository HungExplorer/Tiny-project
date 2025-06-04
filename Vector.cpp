#include "Vector.h"
#include <iostream>
#include <cassert>  // Dùng để kiểm tra chỉ số hợp lệ

using namespace std;

// Constructor: khởi tạo vector với size phần tử và gán tất cả = 0.0
Vector::Vector(int size) : mSize(size) {
    assert(size > 0);  // Đảm bảo size > 0
    mData = new double[mSize];
    for (int i = 0; i < mSize; ++i) {
        mData[i] = 0.0;
    }
}

// Copy constructor
Vector::Vector(const Vector& other) : mSize(other.mSize) {
    mData = new double[mSize];
    for (int i = 0; i < mSize; ++i) {
        mData[i] = other.mData[i];
    }
}

// Destructor
Vector::~Vector() {
    delete[] mData;
}

// Toán tử gán
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

// Trả về kích thước
int Vector::getSize() const {
    return mSize;
}

// Truy cập từ chỉ số 0
double& Vector::operator[](int index) {
    assert(index >= 0 && index < mSize);
    return mData[index];
}

// Truy cập từ chỉ số 1
double& Vector::operator()(int index) {
    assert(index >= 1 && index <= mSize);
    return mData[index - 1];
}

// Cộng hai vector
Vector Vector::operator+(const Vector& other) const {
    assert(mSize == other.mSize);
    Vector result(mSize);
    for (int i = 0; i < mSize; ++i) {
        result.mData[i] = mData[i] + other.mData[i];
    }
    return result;
}

// Trừ hai vector
Vector Vector::operator-(const Vector& other) const {
    assert(mSize == other.mSize);
    Vector result(mSize);
    for (int i = 0; i < mSize; ++i) {
        result.mData[i] = mData[i] - other.mData[i];
    }
    return result;
}

// Nhân vô hướng (dot product) trả về double
double Vector::operator*(const Vector& other) const {
    assert(mSize == other.mSize);
    double result = 0.0;
    for (int i = 0; i < mSize; ++i) {
        result += mData[i] * other.mData[i];
    }
    return result;
}

// Cộng scalar
Vector Vector::operator+(double value) const {
    Vector result(mSize);
    for (int i = 0; i < mSize; ++i) {
        result.mData[i] = mData[i] + value;
    }
    return result;
}

// Trừ scalar
Vector Vector::operator-(double value) const {
    Vector result(mSize);
    for (int i = 0; i < mSize; ++i) {
        result.mData[i] = mData[i] - value;
    }
    return result;
}

// Nhân scalar
Vector Vector::operator*(double value) const {
    Vector result(mSize);
    for (int i = 0; i < mSize; ++i) {
        result.mData[i] = mData[i] * value;
    }
    return result;
}

// Đổi dấu toàn bộ vector
Vector Vector::operator-() const {
    Vector result(mSize);
    for (int i = 0; i < mSize; ++i) {
        result.mData[i] = -mData[i];
    }
    return result;
}

//Data assignment
void Vector::assign(){
    cout << endl << "Enter the elements for vector: " << endl;
    for (int i = 0; i < mSize; i++) 
    {
        cout << "Enter the value for position " << i+1 << ": ";
        cin >> mData[i];
    }
}

//Vector display
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

