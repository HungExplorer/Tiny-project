#include <iostream>
#include "Matrix.h"
#include "Vector.h"
#include "LinearSystem.h"

int main()
{
    Matrix A(3,3);
    Vector b(3);
    A.assign();
    A.display();
    b.assign();
    b.display();
}