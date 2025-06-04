#include "Vector.h"
#include <cassert>
#include <iostream>
using namespace std;

//Constructor
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

//Destructor
Vector::~Vector() {
    delete[] data;
}

//Assigning 
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

//Getting value at index (i)
double& Vector::operator[](int index) {
    assert(index >= 0 && index < size);
    return data[index];
}

double& Vector::operator()(int index) {
    assert(index >= 1 && index <= size);
    return data[index - 1];
}

//Vector operation
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

//Fixed value addition and subtraction/Scalar multiplication
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
//Data assignment
void Vector::assign(){
    cout << endl << "Enter the elements for vector: " << endl;
    for (int i = 0; i < size; i++) 
    {
        cout << "Enter the value for position " << i+1 << ": ";
        cin >> data[i];
    }
}

//Vector display
void Vector::display() const{
    cout << "[";
    for (int i = 0; i < size; i++) 
    {
        if(i != 0)
        {
            cout << " ";
        }
        cout << data[i];
        if (i != size - 1)
            cout << endl;
        else 
            cout << "]" << endl;
    }
}

