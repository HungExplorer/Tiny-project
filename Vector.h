#ifndef VECTOR_H
#define VECTOR_H

// Lớp Vector dùng để biểu diễn một vector 
class Vector {
private:
    int size;              // Số phần tử trong vector
    double* data;          // Con trỏ tới mảng chứa dữ liệu kiểu double

public:
    // Constructor: khởi tạo vector với kích thước cho trước
    Vector(int size);

     // Copy constructor: sao chép vector khác
    Vector(const Vector& other);

     // Destructor: giải phóng vùng nhớ đã cấp phát
    ~Vector();

    // Toán tử gán: gán một vector khác vào vector hiện tại
    Vector& operator=(const Vector& other);

     // Trả về kích thước của vector
    int getSize() const;

    double& operator[](int index);      
    double& operator()(int index);  

    // Cộng hai vector
    Vector operator+(const Vector& other) const;

    // Trừ hai vector
    Vector operator-(const Vector& other) const;

    // Nhân từng phần tử giữa hai vector
    Vector operator*(const Vector& other) const; 

    // Cộng mỗi phần tử trong vector với một số
    Vector operator+(double value) const;

    // Trừ mỗi phần tử trong vector với một số
    Vector operator-(double value) const;

    // Nhân mỗi phần tử trong vector với một số
    Vector operator*(double value) const;
};
#endif
