#ifndef VECTOR_H
#define VECTOR_H

class Vector {
private:
    int mSize;
    double* mData;

public:
    Vector(int size);
    Vector(const Vector& other);
    ~Vector();

    Vector& operator=(const Vector& other);

    int getSize() const;

    // Truy cập phần tử, index từ 0 (operator[])
    double& operator[](int index);

    // Truy cập phần tử, index từ 1 (operator())
    double& operator()(int index);

    Vector operator+(const Vector& other) const;
    Vector operator-(const Vector& other) const;

    // Nếu muốn dot product trả về double:
    double operator*(const Vector& other) const;  

    // Phép toán với scalar
    Vector operator+(double value) const;
    Vector operator-(double value) const;
    Vector operator*(double value) const;

    Vector operator-() const;  // unary minus

    //Gán dữ liệu
    void manualAssign();
    void assign(double* val);

    //Hiển thị
    void display() const; 
};

#endif