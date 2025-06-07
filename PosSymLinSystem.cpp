#include "PosSymLinSystem.h"
#include <cmath>
#include <stdexcept>
PosSymLinSystem::PosSymLinSystem(Matrix A, Vector b)
    : LinearSystem(A, b)
{
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
}
Vector PosSymLinSystem::solve() {
    int n = mSize;
    Vector x(n);
    for (int i = 0; i < n; ++i) {
        x[i] = 0.0;
    }
    Vector r = *mpb;
    Vector p = r;
    double rr_old = r * r;
    const double tol = 1e-10;
    Vector Ap(n);
    for (int k = 0; k < n; ++k) {
        for (int i = 0; i < n; ++i) {
            double sum = 0.0;
            for (int j = 0; j < n; ++j) {
                sum += (*mpA)(i + 1, j + 1) * p[j];
            }
            Ap[i] = sum;
        }
        double pAp = p * Ap;
        if (std::fabs(pAp) < tol) {
            break;
        }
        double alpha = rr_old / pAp;
        for (int i = 0; i < n; ++i) {
            x[i] += alpha * p[i];
        }
        Vector r_new(n);
        for (int i = 0; i < n; ++i) {
            r_new[i] = r[i] - alpha * Ap[i];
        }
        double rr_new = r_new * r_new;
        if (std::sqrt(rr_new) < tol) {
            return x;
        }
        double beta = rr_new / rr_old;
        for (int i = 0; i < n; ++i) {
            p[i] = r_new[i] + beta * p[i];
        }
        r = r_new;
        rr_old = rr_new;
    }
    return x;
}
