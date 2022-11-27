#pragma once

struct Matrix
{
    int row;
    int col;
    float *pMat;
};

struct Matrix *createMatrix(int row, int col);
void valueInMatrix(struct Matrix *p);
void randomValueMatrix(struct Matrix *p);
void deleteMatrix(struct Matrix *mat);
struct Matrix *copyMatrix(const struct Matrix *mat);
struct Matrix *addMatrix(const struct Matrix *mat1, const struct Matrix *mat2);
struct Matrix *subtractMatrix(const struct Matrix *mat1, const struct Matrix *mat2);
struct Matrix *scalarAddition(const struct Matrix *mat, const float a);
struct Matrix *scalarSubtraction(const struct Matrix *mat, const float a);
struct Matrix *scalarMultiplication(const struct Matrix *mat, const float a);
struct Matrix *matmul_plain(const struct Matrix *mat1, const struct Matrix *mat2);
struct Matrix *matmul_improved(const struct Matrix *mat1, const struct Matrix *mat2);
float minMatrix(const struct Matrix *mat);
float maxMatrix(const struct Matrix *mat);
void outPutMatrix(struct Matrix *mat);