#include "mtx.h"
#include <malloc.h>
#include <memory.h>
#include <stdio.h>

#include <omp.h>

Matrix* NewMtx(int n, int m)
{
    int i;
    size_t size;
    Matrix* mtx;
    mtx = (Matrix*)malloc(sizeof(Matrix));

    mtx->rows = n;
    mtx->cols = m;

    mtx->data = (mtxtype**)malloc(sizeof(mtxtype*)*mtx->rows);

    for(i = 0; i < mtx->rows; i++)
    {
        size =sizeof(mtxtype)*mtx->cols;
        mtx->data[i] = (mtxtype*)malloc(size);
        memset(mtx->data[i],0,size);
    }

    return mtx;
}

void FreeMtx(Matrix* mtx)
{
    int i;

    for(i = 0; i < mtx->rows; i++)
    {
        free(mtx->data[i]);
    }

    free(mtx->data);

    free(mtx);
}

void PrintMtx(Matrix* mtx, char* name)
{
    PrintMtxWithSize(mtx,name, 10);
}

void PrintMtxWithSize(Matrix* mtx, char* name, int maxSize)
{
    int i;
    int j;

    int n;
    int m;

    if (maxSize <= 0)
        return;

    n = mtx->rows < maxSize ? mtx->rows : maxSize;
    m = mtx->cols < maxSize ? mtx->cols : maxSize;

    printf("%s\n",name);
    for(i=0; i < n; i++)
    {
        for(j = 0; j < m; j++)
        {
            printf("%d ",mtx->data[i][j]);
        }
        printf("\n");
    }
}

void InitMtx(Matrix* mtx, mtxtype fillConstant)
{
    int i;
    int j;
    //#pragma omp parallel for
    for(i=0; i < mtx->rows; i++)
    {
        for(j = 0; j < mtx->cols; j++)
        {
            mtx->data[i][j] = fillConstant;
        }
    }
}

Matrix* Sum(Matrix* a, Matrix* b, Matrix* c)
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

Matrix* BlockMultiplication(Matrix* a, Matrix* b, Matrix* c)
{
    int i;
    int j;
    int k;

    int n;
    int m;
    int p;

    mtxtype ** aData;
    mtxtype ** bData;
    mtxtype ** cData;
    
    aData = a->data;
    bData = b->data;
    cData = c->data;

#pragma omp parallel
    {
        int threads = omp_get_num_threads();
        int thread = omp_get_thread_num();

        int blockRowSize = a->rows / threads;
        int blockRowColSize = a->cols / threads;
        int blockColSize = b->cols / threads;

        //int blockI = 

        for(i = blockRowSize * thread; i < blockRowSize*(thread+1); i++)
        {
            for(k = blockColSize*thread; k < blockColSize*(thread+1); k++)
            {
                register int result = 0;
                for(j = blockRowColSize*thread; j < blockRowColSize*(thread+1); j++)
                {
                    result += aData[i][j] * bData[k][j];
                }
                cData[i][k] = result;
            }
        }
    }

    return c;
}

Matrix* Multiplication(Matrix* a, Matrix* b, Matrix* c)
{
    int i;
    int j;
    int k;

    int n;
    int m;
    int p;

    mtxtype ** aData;
    mtxtype ** bData;
    mtxtype ** cData;

    n = a->rows;
    m = a->cols;
    p = b->cols;

    aData = a->data;
    bData = b->data;
    cData = c->data;

    Transposition(b);
#pragma omp parallel for
    for(i = 0; i < n; i++)
    {
        for(k = 0; k < p; k++)
        {
            register int result = 0;
//#pragma omp parallel for reduction(+:result)
            for(j = 0; j < m; j++)
            {
                result += aData[i][j] * bData[k][j];
            }
            cData[i][k] = result;
        }
    }

    Transposition(b);
    return c;
}

void Transposition(Matrix* mtx)
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
}