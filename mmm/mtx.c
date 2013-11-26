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
    int i;
    int j;

    if (mtx->rows > 10)
        return;

    printf("%s\n",name);
    for(i=0; i < mtx->rows; i++)
    {
        for(j = 0; j < mtx->cols; j++)
        {
            printf("%d ",mtx->data[i][j]);
        }
        printf("\n");
    }
}

void InitMtx(Matrix* mtx, int fillConstant)
{
    int i;
    int j;
//#pragma omp parallel for
    for(i=0; i < mtx->rows; i++)
    {
        for(j = 0; j < mtx->cols; j++)
        {
            mtx->data[i][j] = fillConstant++;
        }
    }
}

Matrix* Multiplication(Matrix* a, Matrix* b)
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

    Matrix* c;

    c = NewMtx(a->rows, b->cols);

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