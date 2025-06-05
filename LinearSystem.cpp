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

//Helper methods
int LinearSystem::forwardElim()
{
    for (int k = 0; k < mSize; k++)
    {
        // Initialize maximum value and index for pivot
        int i_max = k;
        int v_max = augMatrix[i_max][k];

        /* find greater amplitude for pivot if any */
        for (int i = k + 1; i < mSize; i++)
            if (abs(augMatrix[i][k]) > v_max)
                v_max = augMatrix[i][k], i_max = i;

        /* if a principal diagonal element  is zero,
         * it denotes that matrix is singular, and
         * will lead to a division-by-zero later. */
        if (!augMatrix[k][i_max])
            return k; // Matrix is singular

        /* Swap the greatest value row with current row */
        if (i_max != k)
            swap_row(k, i_max);

        for (int i = k + 1; i < mSize; i++)
        {
            /* factor f to set current row kth element to 0,
             * and subsequently remaining kth column to 0 */
            double f = augMatrix[i][k]/augMatrix[k][k];

            /* subtract fth multiple of corresponding kth
               row element*/
            for (int j = k+1; j <= mSize; j++)
                augMatrix[i][j] -= augMatrix[k][j]*f;

            /* filling lower triangular matrix with zeros*/
            augMatrix[i][k] = 0;
        }

        //print(mat);        //for matrix state
    }
    //print(mat);            //for matrix state
    return -1;
}

Vector LinearSystem::backSub()
{
    double x[mSize];  // An array to store solution

    /* Start calculating from last equation up to the
       first */
    for (int i = mSize-1; i >= 0; i--)
    {
        /* start with the RHS of the equation */
        x[i] = augMatrix[i][mSize];

        /* Initialize j to i+1 since matrix is upper
           triangular*/
        for (int j = i+1; j < mSize; j++)
        {
            /* subtract all the lhs values
             * except the coefficient of the variable
             * whose value is being calculated */
            x[i] -= augMatrix[i][j]*x[j];
        }

        /* divide the RHS by the coefficient of the
           unknown being calculated */
        x[i] = x[i]/augMatrix[i][i];
    }

    cout << "\nSolution for the system:\n";
    // for (int i=0; i< mSize; i++)
    //     cout << x[i];
    Vector sol(mSize);
    sol.assign(x);
    return sol;
}

void LinearSystem::swap_row(int i, int j)
{
    //printf("Swapped rows %d and %d\n", i, j);

    for (int k=0; k <= mSize; k++)
    {
        double temp = augMatrix[i][k];
        augMatrix[i][k] = augMatrix[j][k];
        augMatrix[j][k] = temp;
    }
}

//Gaussian elimination
Vector LinearSystem::solve()
{
    /* reduction into r.e.f. */
    int singular_flag = this->forwardElim();

    /* if matrix is singular */
    if (singular_flag != -1)
    {
        printf("Singular Matrix.\n");

        /* if the RHS of equation corresponding to
           zero row  is 0, * system has infinitely
           many solutions, else inconsistent*/
        if (augMatrix[singular_flag][mSize])
            printf("Inconsistent System.");
        else
            printf("May have infinitely many "
                   "solutions.");

        throw std::runtime_error("Invalid matrix size or singular system.");
    }

    /* get solution to system and print it using
       backward substitution */
    return this->backSub();
}