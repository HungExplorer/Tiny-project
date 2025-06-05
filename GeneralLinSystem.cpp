#include "GeneralLinSystem.h"
#include <cassert>
#include <cmath>

// Constructor: nhận vào Matrix A (m x n) và Vector b (độ dài m)
GeneralLinSystem::GeneralLinSystem(const Matrix& A, const Vector& b)
    : mRows(A.Rows()), mCols(A.Cols())
{
    if (A.Rows() != b.getSize()) {
        throw std::invalid_argument("GeneralLinSystem: Số dòng của A phải bằng độ dài của b.");
    }
    // Sao chép dữ liệu
    mpA = new Matrix(A);
    mpb = new Vector(b);
}

GeneralLinSystem::~GeneralLinSystem() {
    delete mpA;
    delete mpb;
}

int GeneralLinSystem::Rows() const {
    return mRows;
}

int GeneralLinSystem::Cols() const {
    return mCols;
}


// 1) Giải bằng Pseudoinverse: x = A^+ b
//    Giả sử A^+ đã được tính trong Matrix::pseudoInverse()
//    Nếu A là m x n, thì A^+ có kích thước n x m. Kết quả x sẽ là chiều n.
Vector GeneralLinSystem::solvePseudoInverse() const {
    // Tạo A_pinv = pseudoInverse(A)
    Matrix A_pinv = mpA->pseudoInverse();   // A_pinv: n x m

    // Kiểm tra kích thước: A_pinv.Rows() = n = mCols, A_pinv.Cols() = m = mRows
    assert(A_pinv.Rows() == mCols && A_pinv.Cols() == mRows);

    // Tính x = A_pinv * b (Vector độ dài n)
    Vector x(mCols);
    // Công thức:  x[i] = sum_{j=1..m} A_pinv(i+1, j+1) * b[j]
    for (int i = 0; i < mCols; ++i) {
        double sum = 0.0;
        for (int j = 0; j < mRows; ++j) {
            // operator()(i+1, j+1) vì Matrix dùng 1-based
            sum += A_pinv(i + 1, j + 1) * (*mpb)[j];
        }
        x[i] = sum;
    }
    return x;
}


// 2) Giải bằng Tikhonov regularization: 
//    x = (A^T A + λ I)^{-1} A^T b
//    - A là m×n, nên A^T là n×m 
//    - ATA = A^T * A là n×n, + λI cũng n×n → invert
//    - ATb = A^T * b là Vector kích thước n
Vector GeneralLinSystem::solveTikhonov(double lambda) const {
    // Bước 1: Tính A^T
    Matrix At = mpA->transpose();    // At: n x m

    // Bước 2: Tính ATA = At * A (n x n)
    // Matrix::operator*(const Matrix&) thực hiện chuẩn
    Matrix ATA = At * (*mpA);        // kích thước n x n

    // Bước 3: Thêm λ I vào ATA
    for (int i = 1; i <= mCols; ++i) {
        double cur = ATA(i, i);
        ATA(i, i) = cur + lambda;
    }

    // Bước 4: Inverse (ATA + λ I)
    // Nếu ma trận không khả nghịch, sẽ assert hoặc throw
    Matrix invATA = ATA.inverse();   // n x n

    // Bước 5: Tính ATb = A^T * b  → kết quả là Vector độ dài n
    Vector ATb(mCols);
    for (int i = 0; i < mCols; ++i) {
        double sum = 0.0;
        for (int j = 0; j < mRows; ++j) {
            sum += At(i + 1, j + 1) * (*mpb)[j];
        }
        ATb[i] = sum;
    }

    // Bước 6: Tính x = invATA * ATb  → x có kích thước n
    Vector x(mCols);
    for (int i = 0; i < mCols; ++i) {
        double sum = 0.0;
        for (int j = 0; j < mCols; ++j) {
            sum += invATA(i + 1, j + 1) * ATb[j];
        }
        x[i] = sum;
    }

    return x;
}
