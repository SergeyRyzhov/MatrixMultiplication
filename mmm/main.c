#include "Matrix.h"
#include <malloc.h>
#include <omp.h>
#include <stdio.h>
#include <stdlib.h>

int main (int argc, char** argv)
{
    int i = 0;
    int j = 0;
    double time;

    int numThreads = 0;
    
    int maxPrintSize = 10;

    int commonSize = 1000;

    int n;
    int m;
    int k;

    Matrix *a;
    Matrix *b;
    Matrix *c;

    if(argc > 1)
    {
        numThreads = atoi(argv[1]);
        omp_set_num_threads(numThreads);
    }

    if(argc > 2)
    {
        commonSize = atoi(argv[2]);
    }

    if(argc > 3)
    {
        maxPrintSize = atoi(argv[3]);
    }
    n = commonSize;
    m = commonSize;
    k = commonSize;

    a = NewMatrix(n, m);
    b = NewMatrix(m, k);
    c = NewMatrix(n, k);
    
    InitMatrix(a, 0);    
    InitMatrix(b, 0);
    
    PrintMatrixWithSize(a, "a", maxPrintSize);
    PrintMatrixWithSize(b, "b", maxPrintSize);

    time = omp_get_wtime();
    //c = Sum(a,b,c);
    time = omp_get_wtime() - time;
    printf("Sum %f \n", time);    
    
    time = omp_get_wtime();
    c = MatrixMultiplication(a,b,c);
    time = omp_get_wtime() - time;
    printf("Multiplication %f \n", time);
    
    //time = omp_get_wtime();
    //c = BlockMultiplication(a,b,c);
    //time = omp_get_wtime() - time;
    //printf("Block multiplication %f \n", time);
    
    PrintMatrixWithSize(c, "c", maxPrintSize);

    FreeMatrix(a);
    FreeMatrix(b);
    FreeMatrix(c);
    return 0;
}