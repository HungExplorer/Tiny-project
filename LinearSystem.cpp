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
        void getSize()
        {
            return mSize;
        }

        //Assignment method
        void assign(Matrix* pA, Vector* pb)
        {
            //Assigning matrix
            for (int i = 0; i < mSize; i++)
            {
                for (int j = 0; j < mSize; j++)
                {
                    augMatrix[i][j] = (*pA)(i,j);
                }
                //Assigning vector
                augMatrix[i][mSize] = (*pb).data[i];
            }
        }

        //Constructor
        LinearSystem(Matrix A, Vector b)
        {
            if(A.Rows() != A.Cols() || A.Cols() != b.getSize() || A.Rows() != b.getSize())
            {
                throw invalid_argument("Incompatible matrix and vector size, cannot initiate.")
            }
            else
            {
                mSize = B.size;
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
                cout << "Linear System initiated" << endl;
            }
        }

        //Display
        void print()
        {
            for (int i = 0; i < mSize; i++, printf("\n"))
                for (int j = 0; j <= mSize; j++)
                {
                    printf("%lf ", augMatrix[i][j]);
                }
            printf("\n");
        }
        
        //Obliterate default constructors
        LinearSystem(const LinearSystem&) = delete;
        LinearSystem& operator=(const LinearSystem&) = delete;

        ~LinearSystem() 
        {
            for (int i = 0; i < mSize; i++) 
            {
                delete[] augMatrix[i];
            }
            delete[] augMatrix;
            delete mpA;
            delete mpb;
        }
};