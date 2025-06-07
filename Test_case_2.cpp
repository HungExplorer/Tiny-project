#include <iostream>
#include <iomanip>
#include "Matrix.h"
#include "Vector.h"
#include "GeneralLinSystem.h"  

using namespace std;
int main() {
    cout << fixed << setprecision(6);

    // ------------ OVER-DETERMINED (3x2) -------------
    {
        cout << "--- Test Over-determined (3×2) ---\n";
        Matrix A(3, 2);
        Vector b(3);

        A(1,1) = 1;  A(1,2) = 0;
        A(2,1) = 0;  A(2,2) = 1;
        A(3,1) = 1;  A(3,2) = 1;

        b(1) = 1;
        b(2) = 2;
        b(3) = 3;

        cout << "A:\n"; A.display();
        cout << "b: ";  b.display();

        GeneralLinSystem sys(A, b);

        Vector x_pinv = sys.solvePseudoInverse();
        cout << "\n> Pseudoinverse x: ";  x_pinv.display();

        Vector x_tikh = sys.solveTikhonov(0.1);
        cout << "\n> Tikhonov (λ=0.1) x: "; x_tikh.display();
    }

    cout << "\n-----------------------------------\n\n";

    // ------------ UNDER-DETERMINED (2x3) -------------
    {
        cout << "--- Test Under-determined (2×3) ---\n";
        Matrix A(2, 3);
        Vector b(2);
        A(1,1) = 1;  A(1,2) = 2;  A(1,3) = 3;
        A(2,1) = 4;  A(2,2) = 5;  A(2,3) = 6;

        b(1) = 7;
        b(2) = 8;

        cout << "A:\n"; A.display();
        cout << "b: ";  b.display();

        GeneralLinSystem sys(A, b);

        Vector x_pinv = sys.solvePseudoInverse();
        cout << "\n> Pseudoinverse x: "; x_pinv.display();

        Vector x_tikh = sys.solveTikhonov(0.05);
        cout << "\n> Tikhonov (λ=0.05) x: "; x_tikh.display();
    }

    cout << "\n==== END TEST ====\n";
    return 0;
}
