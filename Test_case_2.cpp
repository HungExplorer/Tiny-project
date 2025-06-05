// main.cpp
#include <iostream>
#include <iomanip>  // Dùng để căn chỉnh khi in
#include "Matrix.h"

using namespace std;

int main() {
    cout << fixed << setprecision(4);
    cout << "==== TEST Matrix CLASS ====\n\n";

    // 1. Tạo một ma trận 2x2 và gán giá trị bằng manualAssign()
    int r1 = 2, c1 = 2;
    Matrix A(r1, c1);
    cout << "-- Nhập giá trị cho ma trận A (" << r1 << "x" << c1 << "):\n";
    A.manualAssign();

    cout << "\n-- Ma trận A (2x2):\n";
    A.display();

    // 2. Tạo một ma trận 2x2 khác và gán giá trị trực tiếp qua operator()
    Matrix B(2, 2);
    B(1,1) = 4.0;  B(1,2) = 7.0;
    B(2,1) = 2.0;  B(2,2) = -5.0;

    cout << "\n-- Ma trận B (2x2) đã gán thủ công:\n";
    B.display();

    // 3. Thử phép cộng và trừ hai ma trận 2x2
    Matrix C = A + B;
    cout << "\n-- C = A + B:\n";
    C.display();

    Matrix D = A - B;
    cout << "\n-- D = A - B:\n";
    D.display();

    // 4. Thử nhân hai ma trận 2x2 (A * B)
    Matrix E = A * B;
    cout << "\n-- E = A * B:\n";
    E.display();

    // 5. Thử nhân ma trận với scalar
    double scalar = 3.0;
    Matrix F = A * scalar;
    cout << "\n-- F = A * " << scalar << ":\n";
    F.display();

    // 6. Thử chuyển vị của A
    Matrix At = A.transpose();
    cout << "\n-- At = transpose(A):\n";
    At.display();

    // 7. Tính định thức của A và B
    //   (với A, B là 2x2 nên dễ kiểm tra kết quả)
    double detA = A.determinant();
    cout << "\n-- det(A) = " << detA << "\n";

    double detB = B.determinant();
    cout << "-- det(B) = " << detB << "\n";

    // 8. Thử inverse của B (nếu det(B) != 0)
    if (labs(detB) > 1e-12) {
        Matrix B_inv = B.inverse();
        cout << "\n-- B_inv = inverse(B):\n";
        B_inv.display();

        // Kiểm tra B * B_inv ≈ I
        Matrix I_check = B * B_inv;
        cout << "\n-- B * inverse(B) ≈ I:\n";
        I_check.display();
    } else {
        cout << "\n-- B không khả nghịch (det = 0), bỏ qua inverse\n";
    }

    // 9. Thử với ma trận 3x3 để tính determinant và inverse
    Matrix M3(3, 3);
    // Ví dụ một ma trận có định thức ≠ 0
    M3(1,1) = 1;  M3(1,2) = 2;  M3(1,3) = 3;
    M3(2,1) = 0;  M3(2,2) = -4; M3(2,3) = 1;
    M3(3,1) = 2;  M3(3,2) = 5;  M3(3,3) = -1;

    cout << "\n-- Ma trận M3 (3x3):\n";
    M3.display();

    double detM3 = M3.determinant();
    cout << "\n-- det(M3) = " << detM3 << "\n";

    if (labs(detM3) > 1e-12) {
        Matrix M3_inv = M3.inverse();
        cout << "\n-- M3_inv = inverse(M3):\n";
        M3_inv.display();

        // Kiểm tra M3 * M3_inv ≈ I
        Matrix I3 = M3 * M3_inv;
        cout << "\n-- M3 * inverse(M3) ≈ I:\n";
        I3.display();
    } else {
        cout << "\n-- M3 không khả nghịch (det = 0), bỏ qua inverse\n";
    }

    // 10. Thử pseudo-inverse với ma trận chữ nhật (4x2)
    Matrix R(4, 2);
    // Gán ví dụ:           [ 1  2 ]
    //                      [ 0 -1 ]
    //                      [ 3  5 ]
    //                      [ 2  0 ]
    R(1,1) = 1;   R(1,2) = 2;
    R(2,1) = 0;   R(2,2) = -1;
    R(3,1) = 3;   R(3,2) = 5;
    R(4,1) = 2;   R(4,2) = 0;

    cout << "\n-- Ma trận R (4x2):\n";
    R.display();

    // Tính pseudo-inverse: R_pinv = (R^T * R)^(-1) * R^T
    Matrix R_pinv = R.pseudoInverse();
    cout << "\n-- R_pinv = pseudoInverse(R):\n";
    R_pinv.display();

    // Kiểm tra (R * R_pinv * R) ≈ R
    Matrix temp1 = R * R_pinv * R;
    cout << "\n-- R * R_pinv * R ≈ R:\n";
    temp1.display();

    // 11. Kiểm tra copy constructor và operator=
    Matrix copyM3(M3);
    cout << "\n-- copyM3 (sao chép từ M3):\n";
    copyM3.display();

    // Thay đổi copyM3 không ảnh hưởng M3 gốc
    copyM3(2,2) = 999.0;
    cout << "\n-- Sau khi copyM3(2,2) = 999.0:\n";
    cout << " copyM3:\n";  copyM3.display();
    cout << " M3 (vẫn giữ nguyên):\n";  M3.display();

    Matrix assignTest(3,3);
    assignTest = M3;
    cout << "\n-- assignTest (gán từ M3):\n";
    assignTest.display();

    // Kết thúc
    cout << "\n==== KẾT THÚC TEST Matrix ====\n";
    return 0;
}
