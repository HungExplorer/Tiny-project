#include "Vector.h"
#include <cassert>

// Constructor: khởi tạo vector với kích thước mSize
Vector::Vector(int size) : mSize(size) {
    mData = new double[mSize];
    for (int i = 0; i < mSize; i++) {
        mData[i] = 0.0;
    }
}

// Copy constructor: tạo vector mới bằng cách sao chép vector khác
Vector::Vector(const Vector& other) : mSize(other.mSize) {
    mData = new double[mSize];
    for (int i = 0; i < mSize; i++) {
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
        for (int i = 0; i < mSize; i++) {
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

// Truy cập phần tử từ chỉ số 1 (kiểu toán học)
double& Vector::operator()(int index) {
    assert(index >= 1 && index <= mSize);
    return mData[index - 1];
}

// Toán tử unary âm: -v → đảo dấu từng phần tử
Vector Vector::operator-() const {
    Vector result(mSize);
    for (int i = 0; i < mSize; i++) {
        result.mData[i] = -mData[i];
    }
    return result;
}

// Cộng hai vector cùng kích thước
Vector Vector::operator+(const Vector& other) const {
    assert(mSize == other.mSize);
    Vector result(mSize);
    for (int i = 0; i < mSize; i++) {
        result.mData[i] = mData[i] + other.mData[i];
    }
    return result;
}

// Trừ hai vector cùng kích thước
Vector Vector::operator-(const Vector& other) const {
    assert(mSize == other.mSize);
    Vector result(mSize);
    for (int i = 0; i < mSize; i++) {
        result.mData[i] = mData[i] - other.mData[i];
    }
    return result;
}

// Dot product giữa hai vector: trả về số double
double Vector::operator*(const Vector& other) const {
    assert(mSize == other.mSize);
    double sum = 0.0;
    for (int i = 0; i < mSize; i++) {
        sum += mData[i] * other.mData[i];
    }
    return sum;
}

// Cộng mỗi phần tử trong vector với một số
Vector Vector::operator+(double value) const {
    Vector result(mSize);
    for (int i = 0; i < mSize; i++) {
        result.mData[i] = mData[i] + value;
    }
    return result;
}

// Trừ mỗi phần tử trong vector với một số
Vector Vector::operator-(double value) const {
    Vector result(mSize);
    for (int i = 0; i < mSize; i++) {
        result.mData[i] = mData[i] - value;
    }
    return result;
}

// Nhân mỗi phần tử trong vector với một số
Vector Vector::operator*(double value) const {
    Vector result(mSize);
    for (int i = 0; i < mSize; i++) {
        result.mData[i] = mData[i] * value;
    }
    return result;
}
