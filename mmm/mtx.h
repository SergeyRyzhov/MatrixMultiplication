#ifndef MTX_H
#define MTX_H

#define mtxtype int

//#define SUM(a,b) a + b

typedef struct
{
    int rows;
    int cols;
    mtxtype** data;
} Matrix;

Matrix* NewMtx(int rows, int cols);

void InitMtx(Matrix* mtx, mtxtype fillConstant);

Matrix* Sum(Matrix* a, Matrix* b, Matrix* c);

Matrix* Multiplication(Matrix* a, Matrix* b, Matrix* c);

Matrix* BlockMultiplication(Matrix* a, Matrix* b, Matrix* c);

void FreeMtx(Matrix* mtx);

void PrintMtx(Matrix* mtx, char* name);

void PrintMtxWithSize(Matrix* mtx, char* name, int maxSize);

void Transposition(Matrix* mtx);

#endif