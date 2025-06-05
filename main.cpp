#include <iostream>
#include "Matrix.h"
#include "Vector.h"
#include "LinearSystem.h"

int main()
{
    Matrix A(3,3);
    Vector b(3);
    A.manualAssign();
    A.display();
    b.manualAssign();
    b.display();

    LinearSystem Anb(A,b);
    Anb.display();
    try {
        Vector x = Anb.solve();
        x.display();
    } catch (const std::runtime_error& e) {
        std::cerr << "Solve failed: " << e.what() << std::endl;
    }
}