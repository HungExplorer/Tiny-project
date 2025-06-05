#include "PosSymLinSystem.h"
#include <cmath>
#include <stdexcept>

// Constructor: gọi constructor của LinearSystem, rồi kiểm tra tính đối xứng
PosSymLinSystem::PosSymLinSystem(Matrix A, Vector b)
    : LinearSystem(A, b)   // Gọi vào LinearSystem::LinearSystem(A, b)
{
    // Kiểm tra tính đối xứng của ma trận mpA (mData của mpA)
    // mpA là pointer đến Matrix đã được cấp phát trong lớp cha
    int n = mSize;
    const double tol = 1e-12;

    for (int i = 1; i <= n; ++i) {
        for (int j = i + 1; j <= n; ++j) {
            double a_ij = (*mpA)(i, j);
            double a_ji = (*mpA)(j, i);
            if (std::fabs(a_ij - a_ji) > tol) {
                throw std::invalid_argument("Matrix is not symmetric.");
            }
        }
    }
    // Nếu tới đây thì ma trận đối xứng, tiếp tục sử dụng Conjugate Gradient
}

// Phương thức solve() override: dùng Conjugate Gradient để giải Ax = b
Vector PosSymLinSystem::solve() {
    int n = mSize;
    // Lấy con trỏ mpA và mpb từ lớp cha
    // (*mpA)(i,j) trả về phần tử ở i-th dòng, j-th cột (1-based)
    // (*mpb)(i) trả về phần tử i-th của vector b (1-based)

    // Khởi tạo x = [0, 0, ..., 0]^T
    Vector x(n);
    for (int i = 0; i < n; ++i) {
        x[i] = 0.0;
    }

    // Khởi tạo r = b - A*x  → vì x=0 nên r = b
    Vector r = *mpb;  

    // Khởi tạo p = r
    Vector p = r;

    // Tính rr_old = r^T r
    double rr_old = r * r;    // operator* của Vector đã tính dot product

    const double tol = 1e-10;
    Vector Ap(n);

    for (int k = 0; k < n; ++k) {
        // Tính Ap = A * p
        for (int i = 0; i < n; ++i) {
            double sum = 0.0;
            for (int j = 0; j < n; ++j) {
                // Lưu ý: operator() nhận index 1-based
                sum += (*mpA)(i + 1, j + 1) * p[j];
            }
            Ap[i] = sum;
        }

        // Tính alpha = (r^T r) / (p^T Ap)
        double pAp = p * Ap;
        if (std::fabs(pAp) < tol) {
            // Có thể coi là chia cho gần 0 → dừng
            break;
        }
        double alpha = rr_old / pAp;

        // Cập nhật x = x + alpha * p
        for (int i = 0; i < n; ++i) {
            x[i] += alpha * p[i];
        }

        // Cập nhật r_new = r - alpha * Ap
        Vector r_new(n);
        for (int i = 0; i < n; ++i) {
            r_new[i] = r[i] - alpha * Ap[i];
        }

        // Kiểm tra điều kiện dừng: ||r_new||^2 < tol^2
        double rr_new = r_new * r_new;
        if (std::sqrt(rr_new) < tol) {
            // Gần hội tụ → gán x và thoát
            return x;
        }

        // Tính beta = (r_new^T r_new) / (r^T r)
        double beta = rr_new / rr_old;

        // Cập nhật p = r_new + beta * p
        for (int i = 0; i < n; ++i) {
            p[i] = r_new[i] + beta * p[i];
        }

        // Cập nhật r = r_new, rr_old = rr_new
        r = r_new;
        rr_old = rr_new;
    }

    return x;
}
