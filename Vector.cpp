#include "Vector.h"
#include <cassert>

// Constructor: khởi tạo vector với số phần tử là size
// Cấp phát bộ nhớ động cho mảng data và gán tất cả phần tử = 0.0
Vector::Vector(int size) : size(size) {
    data = new double[size];
    for (int i = 0; i < size; i++) {
        data[i] = 0.0;
    }
}

// Copy constructor: tạo vector mới bằng cách sao chép vector khác
// Dùng khi khai báo kiểu: Vector b = a;
Vector::Vector(const Vector& other) : size(other.size) {
    data = new double[size];
    for (int i = 0; i < size; i++) {
        data[i] = other.data[i];
    }
}

// Destructor: giải phóng bộ nhớ
Vector::~Vector() {
    delete[] data;
}

// Toán tử gán: gán vector khác vào vector hiện tại
Vector& Vector::operator=(const Vector& other) {
    if (this != &other) {          // kiểm tra không tự gán chính nó
        delete[] data;             // xóa mảng cũ để tránh memory leak
        
        size = other.size;         // gán lại kích thước từ vector bên phải
        data = new double[size];   // cấp phát mảng mới với size mới
        for (int i = 0; i < size; i++) {
            data[i] = other.data[i];       // sao chép từng phần tử từ vector kia
        }
    }
    return *this;
}

// Trả về kích thước của vector
int Vector::getSize() const {
    return size;
}

// Truy cập phần tử từ chỉ số 0
double& Vector::operator[](int index) {
    assert(index >= 0 && index < size);
    return data[index];
}

// Truy cập phần tử từ chỉ số 1 (dạng toán học)
double& Vector::operator()(int index) {
    assert(index >= 1 && index <= size);
    return data[index - 1];
}

// Cộng hai vector
Vector Vector::operator+(const Vector& other) const {
    assert(size == other.size);
    Vector result(size);
    for (int i = 0; i < size; i++) {
        result.data[i] = data[i] + other.data[i];
    }
    return result;
}

// Trừ hai vector
Vector Vector::operator-(const Vector& other) const {
    assert(size == other.size);
    Vector result(size);
    for (int i = 0; i < size; i++) {
        result.data[i] = data[i] - other.data[i];
    }
    return result;
}

// Nhân từng phần tử giữa hai vector
Vector Vector::operator*(const Vector& other) const {
    assert(size == other.size);
    Vector result(size);
    for (int i = 0; i < size; i++) {
        result.data[i] = data[i] * other.data[i];
    }
    return result;
}

// Cộng mỗi phần tử trong vector với một số
Vector Vector::operator+(double value) const {
    Vector result(size);
    for (int i = 0; i < size; i++) {
        result.data[i] = data[i] + value;
    }
    return result;
}

// Trừ mỗi phần tử trong vector với một số
Vector Vector::operator-(double value) const {
    Vector result(size);
    for (int i = 0; i < size; i++) {
        result.data[i] = data[i] - value;
    }
    return result;
}

// Nhân mỗi phần tử trong vector với một số
Vector Vector::operator*(double value) const {
    Vector result(size);
    for (int i = 0; i < size; i++) {
        result.data[i] = data[i] * value;
    }
    return result;
}
