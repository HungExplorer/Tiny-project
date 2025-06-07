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

    double& operator[](int index);
    double& operator()(int index);

    Vector operator+(const Vector& other) const;
    Vector operator-(const Vector& other) const;
    double operator*(const Vector& other) const;  

    Vector operator+(double value) const;
    Vector operator-(double value) const;
    Vector operator*(double value) const;
    Vector operator-() const;  

    void manualAssign();
    void assign(double* val);
    void display() const; 
};
#endif
