#ifndef GENERALLINSYSTEM_H
#define GENERALLINSYSTEM_H

#include "Matrix.h"
#include "Vector.h"
#include <stdexcept>

class GeneralLinSystem {
private:
    int mRows;      // số dòng của A (m)
    int mCols;      // số cột của A (n)
    Matrix* mpA;    // con trỏ đến ma trận A (m x n)
    Vector* mpb;    // con trỏ đến vector b (độ dài m)

public:
    // Constructor: sao chép A và b
    // Yêu cầu A.Rows() == b.getSize()
    GeneralLinSystem(const Matrix& A, const Vector& b);

    // Destructor: giải phóng bộ nhớ
    ~GeneralLinSystem();

    // Trả về số dòng và số cột
    int Rows() const;
    int Cols() const;

    // Giải hệ bằng ma trận Pseudoinverse: x = A^+ b
    // Trả về Vector x có độ dài = n (mCols)
    Vector solvePseudoInverse() const;

    // Giải hệ với Tikhonov regularization:
    //   x = (A^T A + λ I)^{-1} A^T b
    // Trả về Vector x có độ dài = n (mCols)
    Vector solveTikhonov(double lambda) const;

    // Không cho phép sử dụng copy constructor hoặc operator= mặc định
    GeneralLinSystem(const GeneralLinSystem&) = delete;
    GeneralLinSystem& operator=(const GeneralLinSystem&) = delete;
};

#endif // GENERALLINSYSTEM_H
