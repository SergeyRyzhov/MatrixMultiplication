#ifndef MATRIX_H
#define MATRIX_H

#include <malloc.h>
#include <memory.h>
#include <stdio.h>

#include <omp.h>

#define MatrixElementType double
#define MatrixIndexType int

typedef struct
{
    MatrixIndexType rows;
    MatrixIndexType cols;
    MatrixIndexType size;

    MatrixElementType* data;
} Matrix;

Matrix* NewMatrix(MatrixIndexType rows, MatrixIndexType cols);

void FreeMatrix(Matrix* matrix);

void InitMatrix(Matrix* matrix, MatrixElementType fillConstant);

void PrintMatrix(Matrix* matrix, char* name);

void PrintMatrixWithSize(Matrix* matrix, char* name, MatrixIndexType maxSize);

Matrix* MatrixMultiplication(Matrix* a, Matrix* b, Matrix* c);

#endif