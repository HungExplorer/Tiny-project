#ifndef LINEAR_H
#define LINEAR_H
#include <iostream>
#include "Matrix.h"
#include "Vector.h"
using namespace std;
class LinearSystem
{
    protected:
        int mSize;
        Matrix* mpA;
        Vector* mpb;
        double** augMatrix;
    public:
        int getSize();
        void assign(Matrix* pA, Vector* pb);
        LinearSystem(Matrix A, Vector b);
        void display();
        LinearSystem(const LinearSystem&) = delete;
        LinearSystem& operator=(const LinearSystem&) = delete;
        ~LinearSystem(); 
        int forwardElim();
        Vector backSub();
        void swap_row(int i, int j);
        virtual Vector solve();
};
// int forwardElim(double** augMatrix);
// void backSub(double** augMatrix);
// void swap_row(double** augMatrix, int i, int j);
#endif
