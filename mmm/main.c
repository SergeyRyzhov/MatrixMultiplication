#include "mtx.h"
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

    n = commonSize;
    m = commonSize;
    k = commonSize;

    a = NewMtx(n, m);
    b = NewMtx(m, k);
    
    InitMtx(a,1);    
    InitMtx(b,1);
    
    PrintMtx(a, "a");
    PrintMtx(b, "b");

    time = omp_get_wtime();
    c = Multiplication(a,b);
    time = omp_get_wtime() - time;

    printf("%f \n", time);

    PrintMtx(c, "c");

    FreeMtx(a);
    FreeMtx(b);
    FreeMtx(c);
    return 0;
}