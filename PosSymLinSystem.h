#ifndef POSSYMLINSYSTEM_H
#define POSSYMLINSYSTEM_H

#include "LinearSystem.h"

class PosSymLinSystem : public LinearSystem {
public:
    // Constructor: gọi thẳng vào constructor của LinearSystem
    // Sau đó kiểm tra tính đối xứng của ma trận mpA
    PosSymLinSystem(Matrix A, Vector b);

    // Override phương thức solve() để dùng Conjugate Gradient
    Vector solve() override;
};

#endif // POSSYMLINSYSTEM_H
