#include "Vector.h"
#include <cassert>  // Kiểm tra chỉ số và điều kiện hợp lệ

// Constructor: khởi tạo vector với mSize phần tử, gán tất cả = 0.0
Vector::Vector(int size) : mSize(size) {
    assert(size > 0);  // Đảm bảo kích thước hợp lệ
    mData = new double[mSize];
    for (int i = 0; i < mSize; ++i) {
        mData[i] = 0.0;
    }
}

// Copy constructor: tạo bản sao của vector khác
Vector::Vector(const Vector& other) : mSize(other.mSize) {
    mData = new double[mSize];
    for (int i = 0; i < mSize; ++i) {
        mData[i] = other.mData[i];
    }
}

// Destructor: giải phóng bộ nhớ
Vector::~Vector() {
    delete[] mData;
}

// Toán tử gán: gán vector khác vào vector hiện tại
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

// Trả về kích thước vector
int Vector::getSize() const {
    return mSize;
}

// Truy cập phần tử từ chỉ số 0
double& Vector::operator[](int index) {
    assert(index >= 0 && index < mSize);
    return mData[index];
}

// Truy cập phần tử từ chỉ số 1 (dạng toán học)
double& Vector::operator()(int index) {
    assert(index >= 1 && index <= mSize);
    return mData[index - 1];
}

// Toán tử unary âm: đảo dấu từng phần tử
Vector Vector::operator-() const {
    Vector result(mSize);
    for (int i = 0; i < mSize; ++i) {
        result.mData[i] = -mData[i];
    }
    return result;
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

// Nhân vô hướng (dot product) → trả về số thực
double Vector::operator*(const Vector& other) const {
    assert(mSize == other.mSize);
    double result = 0.0;
    for (int i = 0; i < mSize; ++i) {
        result += mData[i] * other.mData[i];
    }
    return result;
}

// Cộng vector với số
Vector Vector::operator+(double value) const {
    Vector result(mSize);
    for (int i = 0; i < mSize; ++i) {
        result.mData[i] = mData[i] + value;
    }
    return result;
}

// Trừ số khỏi vector
Vector Vector::operator-(double value) const {
    Vector result(mSize);
    for (int i = 0; i < mSize; ++i) {
        result.mData[i] = mData[i] - value;
    }
    return result;
}

// Nhân vector với số
Vector Vector::operator*(double value) const {
    Vector result(mSize);
    for (int i = 0; i < mSize; ++i) {
        result.mData[i] = mData[i] * value;
    }
    return result;
}
