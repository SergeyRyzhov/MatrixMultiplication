#include "matrix.h"
#include <malloc.h>
#include <memory.h>
#include <stdio.h>

#include <omp.h>

#define mtxtype MatrixElementType
#define inxtype MatrixIndexType

//#define AligmentSize 16
#define maxelem 10

Matrix* NewMatrix(inxtype m, inxtype n)
{
    Matrix* mtx;
    mtx = (Matrix*)malloc(sizeof(Matrix));

    mtx->rows = m;
    mtx->cols = n;

    mtx->size = m * n;
#ifdef AligmentSize
    mtx->data = (mtxtype*)_aligned_malloc(sizeof(mtxtype) * mtx->size, AligmentSize);
#else
    mtx->data = (mtxtype*)malloc(sizeof(mtxtype) * mtx->size);
#endif
    
    memset(mtx->data, 0, mtx->size);
    return mtx;
}

void FreeMatrix(Matrix* mtx)
{

#ifdef AligmentSize
    _aligned_free(mtx->data);
    _aligned_free(mtx);
#else
    free(mtx->data);
    free(mtx);
#endif    
}

void InitMatrix(Matrix* mtx, mtxtype ctx)
{
    inxtype i;
    if (0 == ctx)
    {
        for(i = 0; i < mtx->size; i++)
        {
            mtx->data[i] = (mtxtype)(rand() % maxelem + 1);
        }
    }
    else
    {
        for(i = 0; i < mtx->size; i++)
        {
            mtx->data[i] = ctx;
        }
    }
}

void PrintMatrix(Matrix* mtx, char* name)
{
    PrintMatrixWithSize(mtx, name, 10);
}

void PrintMatrixWithSize(Matrix* mtx, char* name, inxtype maxSize)
{
    inxtype i;
    inxtype j;

    inxtype n;
    inxtype m;

    if (maxSize <= 0)
        return;

    n = mtx->cols < maxSize ? mtx->cols : maxSize;
    m = mtx->rows < maxSize ? mtx->rows : maxSize;

    printf("%s\n",name);

    for(i = 0; i < m; i++)
    {
        for(j = 0; j < n; j++)
        {
            printf("%f ", mtx->data[i * mtx->cols + j]);
        }
        printf("\n");
    }
}

_declspec(noinline) Matrix* MatrixMultiplication(Matrix* a, Matrix* b, Matrix* c)
{
    inxtype i;
    inxtype j;
    inxtype k;

    inxtype n;
    inxtype m;
    inxtype p;

    //mtxtype* __restrict aData;
    //mtxtype* __restrict bData;
    //mtxtype* __restrict cData;


    n = a->rows;
    m = a->cols;
    p = b->cols;

    //Transposition(b);

#pragma omp parallel for //private(aData, bData, cData)// schedule(dynamic, 64)
    for(i = 0; i < n; i++)
    {
        mtxtype* __restrict aData = a->data + i * m;
        mtxtype* __restrict cData = c->data + i * p;

        for(k = 0; k < p; k++)
        {
            register int result = 0;

            mtxtype* __restrict bData = b->data + k * p;
//#pragma omp parallel for reduction(+:result)
#pragma simd reduction(+:result)
            for(j = 0; j < m; j++)
            {
                result += aData[j] * bData[j];
            }

           cData[k] = result;
        }
    }

    //Transposition(b);
    return c;
}


/*
Mtx* Sum(Mtx* a, Mtx* b, Mtx* c)
{
    int i;
    int j;
    
    mtxtype * aData;
    mtxtype * bData;
    mtxtype * cData;

#pragma omp parallel for
    for (i = 0; i < a->rows; i++)
    {
        aData = a->data[i];
        bData = b->data[i];
        cData = c->data[i];
        for (j = 0; j < a->cols; j++)
        {
            cData[j] = aData[j] + bData[j];
        }
    }

    return c;
}

void Transposition(Mtx* mtx)
{
    int i;
    int j;
    int t;
    //#pragma omp parallel for
    for(i = 0; i < mtx->rows; i++)
    {
        for(j = i + 1; j < mtx->cols; j++)
        {
            t = mtx->data[i][j];
            mtx->data[i][j] = mtx->data[j][i];
            mtx->data[j][i] = t;
        }
    }
}*/