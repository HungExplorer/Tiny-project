#include <iostream>
#include "Matrix.h"
#include "Vector.h"
#include "LinearSystem.h"
using namespace std;

int LinearSystem::getSize()
{
    return mSize;
}

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

        augMatrix = new double*[mSize];
        for (int i = 0; i < mSize; ++i) 
        {
            augMatrix[i] = new double[mSize + 1];
        }

        assign(mpA, mpb);
        cout << endl << "Linear System initiated" << endl;
    }
}

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
            cout << augMatrix[i][j];
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

void LinearSystem::assign(Matrix* pA, Vector* pb)
{
    for (int i = 0; i < mSize; i++)
    {
        for (int j = 0; j < mSize; j++)
        {
            augMatrix[i][j] = (*pA)(i + 1,j + 1);
        }
        augMatrix[i][mSize] = (*pb)(i + 1);
    }
}

int LinearSystem::forwardElim()
{
    for (int k = 0; k < mSize; k++)
    {
        int i_max = k;
        int v_max = augMatrix[i_max][k];

        for (int i = k + 1; i < mSize; i++)
            if (abs(augMatrix[i][k]) > v_max)
                v_max = augMatrix[i][k], i_max = i;

        if (!augMatrix[k][i_max])
            return k;

        if (i_max != k)
            swap_row(k, i_max);

        for (int i = k + 1; i < mSize; i++)
        {
            double f = augMatrix[i][k]/augMatrix[k][k];
            for (int j = k+1; j <= mSize; j++)
                augMatrix[i][j] -= augMatrix[k][j]*f;
            augMatrix[i][k] = 0;
        }
    }
    return -1;
}

Vector LinearSystem::backSub()
{
    double x[mSize];
    for (int i = mSize-1; i >= 0; i--)
    {
        x[i] = augMatrix[i][mSize];
        for (int j = i+1; j < mSize; j++)
        {
            x[i] -= augMatrix[i][j]*x[j];
        }
        x[i] = x[i]/augMatrix[i][i];
    }

    cout << "\nSolution for the system:\n";
    Vector sol(mSize);
    sol.assign(x);
    return sol;
}

void LinearSystem::swap_row(int i, int j)
{
    for (int k=0; k <= mSize; k++)
    {
        double temp = augMatrix[i][k];
        augMatrix[i][k] = augMatrix[j][k];
        augMatrix[j][k] = temp;
    }
}

Vector LinearSystem::solve()
{
    int singular_flag = this->forwardElim();

    if (singular_flag != -1)
    {
        printf("Singular Matrix.\n");

        if (augMatrix[singular_flag][mSize])
            printf("Inconsistent System.");
        else
            printf("May have infinitely many solutions.");

        throw std::runtime_error("Invalid matrix size or singular system.");
    }

    return this->backSub();
}
