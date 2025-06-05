#ifndef VECTOR_H
#define VECTOR_H

// Lớp Vector biểu diễn vector số thực 1 chiều
class Vector {
private:
    int mSize;          // Kích thước vector
    double* mData;      // Mảng chứa các giá trị thực

public:
    // Constructor: khởi tạo vector với kích thước
    Vector(int size);

    // Copy constructor: sao chép vector khác
    Vector(const Vector& other);

    // Destructor: giải phóng bộ nhớ
    ~Vector();

    // Toán tử gán: gán vector khác vào vector hiện tại
    Vector& operator=(const Vector& other);

    // Trả về kích thước vector
    int getSize() const;

    // Truy cập phần tử từ 0 (kiểu mảng)
    double& operator[](int index);

    // Truy cập phần tử từ 1 (kiểu toán học)
    double& operator()(int index);

    // Toán tử unary âm: -v
    Vector operator-() const;

    // Cộng 2 vector
    Vector operator+(const Vector& other) const;

    // Trừ 2 vector
    Vector operator-(const Vector& other) const;

    // Dot product giữa 2 vector → trả về số thực
    double operator*(const Vector& other) const;

    // Phép toán với số (scalar)
    Vector operator+(double value) const;
    Vector operator-(double value) const;
    Vector operator*(double value) const;
};

#endif
