#include <iostream>
#include "Matrix.h"
#include "Vector.h"
#include "LinearSystem.h"

using namespace std;

//size getter
int LinearSystem::getSize()
{
    return mSize;
}

//Constructor
LinearSystem::LinearSystem(Matrix A, Vector b)
{
    if(A.Rows() != A.Cols() || A.Cols() != b.getSize() || A.Rows() != b.getSize())
    {
        throw invalid_argument("Incompatible matrix and vector size, cannot initiate.");
    }
    else
    {
        mSize = b.getSize();
        mpA = new Matrix(A);
        mpb = new Vector(b);
        
        //Allocate array of int* (for rows)
        augMatrix = new double*[mSize];

        //Allocate each row (array of double)
        for (int i = 0; i < mSize; ++i) 
        {
            augMatrix[i] = new double[mSize + 1];
        }

        assign(mpA, mpb);
        cout << endl << "Linear System initiated" << endl;
    }
}

//Display
void LinearSystem::display()
{
    cout << endl << "[";
    for (int i = 0; i < mSize; ++i)
    {
        if (i != 0)
        {
            cout << " ";
        }    
        for (int j = 0; j <= mSize; ++j)
        {
            cout<< augMatrix[i][j];
            if (j != mSize)
            {
                if(j == mSize - 1)
                {
                    cout << " |";
                }
                cout << " ";
            }
            if (j == mSize && i != mSize - 1)
            {
                cout << endl;
            }
            if (j == mSize && i == mSize - 1)
            {
                cout << "]" << endl;
            }
        }
    }
}

LinearSystem::~LinearSystem() 
{
    for (int i = 0; i < mSize; i++) 
    {
        delete[] augMatrix[i];
    }
    delete[] augMatrix;
    delete mpA;
    delete mpb;
}


//Assignment method
void LinearSystem::assign(Matrix* pA, Vector* pb)
{
    //Assigning matrix
    for (int i = 0; i < mSize; i++)
    {
        for (int j = 0; j < mSize; j++)
        {
            augMatrix[i][j] = (*pA)(i + 1,j + 1);
        }
        //Assigning vector
        augMatrix[i][mSize] = (*pb)(i + 1);
    }
}