#include "Vector.h"
#include <cassert>

Vector::Vector(int size) : size(size) {
    data = new double[size];
    for (int i = 0; i < size; i++) {
        data[i] = 0.0;
    }
}

Vector::Vector(const Vector& other) : size(other.size) {
    data = new double[size];
    for (int i = 0; i < size; i++) {
        data[i] = other.data[i];
    }
}

Vector::~Vector() {
    delete[] data;
}

Vector& Vector::operator=(const Vector& other) {
    if (this != &other) {
        delete[] data;
        size = other.size;
        data = new double[size];
        for (int i = 0; i < size; i++) {
            data[i] = other.data[i];
        }
    }
    return *this;
}

int Vector::getSize() const {
    return size;
}

double& Vector::operator[](int index) {
    assert(index >= 0 && index < size);
    return data[index];
}

double& Vector::operator()(int index) {
    assert(index >= 1 && index <= size);
    return data[index - 1];
}

Vector Vector::operator+(const Vector& other) const {
    assert(size == other.size);
    Vector result(size);
    for (int i = 0; i < size; i++) {
        result.data[i] = data[i] + other.data[i];
    }
    return result;
}

Vector Vector::operator-(const Vector& other) const {
    assert(size == other.size);
    Vector result(size);
    for (int i = 0; i < size; i++) {
        result.data[i] = data[i] - other.data[i];
    }
    return result;
}

Vector Vector::operator*(const Vector& other) const {
    assert(size == other.size);
    Vector result(size);
    for (int i = 0; i < size; i++) {
        result.data[i] = data[i] * other.data[i];
    }
    return result;
}

Vector Vector::operator+(double value) const {
    Vector result(size);
    for (int i = 0; i < size; i++) {
        result.data[i] = data[i] + value;
    }
    return result;
}

Vector Vector::operator-(double value) const {
    Vector result(size);
    for (int i = 0; i < size; i++) {
        result.data[i] = data[i] - value;
    }
    return result;
}

Vector Vector::operator*(double value) const {
    Vector result(size);
    for (int i = 0; i < size; i++) {
        result.data[i] = data[i] * value;
    }
    return result;
}
