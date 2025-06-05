// Ví dụ sử dụng trong main.cpp

#include <iostream>
#include "Matrix.h"
#include "Vector.h"
#include "LinearSystem.h"
#include "PosSymLinSystem.h"

using namespace std;

int main() {
    // Tạo ma trận A (3x3) và vector b (3)
    Matrix A(3, 3);
    Vector b(3);

    // Gán ví dụ:
    // A = [ 4 1 0 ]
    //     [ 1 3 1 ]
    //     [ 0 1 2 ]
    A(1,1) = 4;  A(1,2) = 1;  A(1,3) = 0;
    A(2,1) = 1;  A(2,2) = 3;  A(2,3) = 1;
    A(3,1) = 0;  A(3,2) = 1;  A(3,3) = 2;

    b(1) = 1;
    b(2) = 2;
    b(3) = 3;

    cout << "--- Giải bằng Gaussian Elimination (LinearSystem) ---\n";
    LinearSystem sys1(A, b);
    Vector x1 = sys1.solve();
    x1.display();

    cout << "\n--- Giải bằng Conjugate Gradient (PosSymLinSystem) ---\n";
    PosSymLinSystem sys2(A, b);
    Vector x2 = sys2.solve();
    x2.display();

    return 0;
}
