#ifndef MTX_H
#define MTX_H


#define mtxtype int

typedef struct
{
    int rows;
    int cols;
    mtxtype** data;
} Matrix;

Matrix* NewMtx(int rows, int cols);

void InitMtx(Matrix* mtx, int fillConstant);

Matrix* Multiplication(Matrix* a, Matrix* b);

void FreeMtx(Matrix* mtx);

void PrintMtx(Matrix* mtx, char* name);

void Transposition(Matrix* mtx);

#endif