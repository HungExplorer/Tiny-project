#ifndef LINEAR_H
#define LINEAR_H

#include <iostream>
#include "Matrix.h"
#include "Vector.h"

using namespace std;

class LinearSystem
{
    private:
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

        //Gaussian elimination
        virtual void solve();

        //Display
        void display();
        
        //Obliterate default constructors
        LinearSystem(const LinearSystem&) = delete;
        LinearSystem& operator=(const LinearSystem&) = delete;

        ~LinearSystem(); 
};

#endif