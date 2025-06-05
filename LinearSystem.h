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
        //size getter
        int getSize();

        //Assignment method
        void assign(Matrix* pA, Vector* pb);

        //Constructor
        LinearSystem(Matrix A, Vector b);

        //Display
        void display();
        
        //Obliterate default constructors
        LinearSystem(const LinearSystem&) = delete;
        LinearSystem& operator=(const LinearSystem&) = delete;

        //Destructor
        ~LinearSystem(); 

        //Helper methods
        int forwardElim();
        Vector backSub();
        void swap_row(int i, int j);

        //Gaussian elimination
        virtual Vector solve();
};

// int forwardElim(double** augMatrix);
// void backSub(double** augMatrix);
// void swap_row(double** augMatrix, int i, int j);

#endif
