#ifndef POSSYMLINSYSTEM_H
#define POSSYMLINSYSTEM_H
#include "LinearSystem.h"
class PosSymLinSystem : public LinearSystem {
public:
    PosSymLinSystem(Matrix A, Vector b);
    Vector solve() override;
};
#endif 
