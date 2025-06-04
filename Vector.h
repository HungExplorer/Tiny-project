#ifndef VECTOR_H
#define VECTOR_H

class Vector {
private:
    int size;
    double* data;

public:
    //Constructor
    Vector(int size);
    Vector(const Vector& other);

    //Destructor
    ~Vector();

    //Assigning
    Vector& operator=(const Vector& other);

    //Size getter
    int getSize() const;

    //Accessing value at index (i)
    double& operator[](int index);      
    double& operator()(int index);      

    //Operator
    Vector operator+(const Vector& other) const;
    Vector operator-(const Vector& other) const;
    Vector operator*(const Vector& other) const; 

    //Fixed value addition and subtraction/Scalar multiplication
    Vector operator+(double value) const;
    Vector operator-(double value) const;
    Vector operator*(double value) const;

    //Data assignment
    void assign();

    //Vector display
    void display() const;
};

#endif
