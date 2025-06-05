// main.cpp
#include <iostream>
#include "Vector.h"

using namespace std;

int main() {
    cout << "==== TEST Vector CLASS ====\n\n";

    // 1. Tạo 2 vector kích thước 3 và gán giá trị cho chúng
    int n = 3;
    Vector v1(n);
    Vector v2(n);

    // Gán giá trị cho v1 bằng cách sử dụng mảng tạm
    double data1[] = { 1.0, 2.0, 3.0 };
    v1.assign(data1);

    // Gán giá trị cho v2 theo cách thủ công (dùng operator[])
    v2[0] = 4.5;
    v2[1] = -1.0;
    v2[2] = 10.0;

    cout << "-- Vector v1 (sau khi assign):\n";
    v1.display();

    cout << "-- Vector v2 (sau khi gán trực tiếp):\n";
    v2.display();

    // 2. Thử truy xuất phần tử với operator[] (0-based) và operator() (1-based)
    cout << "\n-- Truy xuat phan tu:\n";
    cout << " v1[0] = " << v1[0] << "   (should be 1.0)\n";
    cout << " v1(3) = " << v1(3) << "   (should be 3.0)\n";

    // Thay đổi v1(2) (index 1-based) và v2[2] (index 0-based)
    v1(2) = 20.0;   // v1[1] = 20.0
    v2[2] = 7.5;    // v2[2] = 7.5

    cout << "\n-- Sau khi chỉnh sửa v1(2) = 20.0 và v2[2] = 7.5:\n";
    cout << " v1: "; v1.display();
    cout << " v2: "; v2.display();

    // 3. Thử phép cộng hai vector (operator+)
    Vector sum = v1 + v2;
    cout << "\n-- v1 + v2 = ";
    sum.display();

    // 4. Thử phép trừ hai vector (operator-)
    Vector diff = v1 - v2;
    cout << "\n-- v1 - v2 = ";
    diff.display();

    // 5. Thử dot product (operator*)
    double dot = v1 * v2;
    cout << "\n-- Dot product v1 * v2 = " << dot << "   (tổng 1*4.5 + 20*(-1.0) + 3*7.5)\n";

    // 6. Thử unary minus (-v1)
    Vector neg = -v1;
    cout << "\n-- -v1 = ";
    neg.display();

    // 7. Thử các phép toán với scalar
    double scalar = 2.0;
    Vector addScalar = v1 + scalar;
    Vector subScalar = v1 - scalar;
    Vector mulScalar = v1 * scalar;

    cout << "\n-- v1 + " << scalar << " = ";
    addScalar.display();

    cout << "\n-- v1 - " << scalar << " = ";
    subScalar.display();

    cout << "\n-- v1 * " << scalar << " = ";
    mulScalar.display();

    // 8. Thử copy constructor
    Vector copied(v1);
    cout << "\n-- Vector copied (sao chép từ v1) = ";
    copied.display();

    // 9. Thử operator= (assignment)
    Vector assigned(3);
    assigned = v2;   // gán giá trị v2 vào assigned
    cout << "\n-- Vector assigned (gán từ v2) = ";
    assigned.display();

    // 10. Thay đổi assigned để kiểm tra rằng deep copy được thực hiện
    assigned(1) = 999.0;  // chỉ sửa assigned, không ảnh hưởng v2
    cout << "\n-- Sau khi sửa assigned(1) = 999.0:\n";
    cout << " assigned = "; assigned.display();
    cout << " v2 (vẫn phải giữ nguyên) = "; v2.display();

    cout << "\n==== KET THUC TEST ====\n";
    return 0;
}
