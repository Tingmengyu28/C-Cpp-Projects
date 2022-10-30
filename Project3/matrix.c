#include <stdio.h>
#include <stdlib.h>
#include "matrix.h"

struct Matrix *createMatrix(int row, int col)
{
    struct Matrix *p = (struct Matrix *)malloc(sizeof(struct Matrix));
    p->row = row;
    p->col = col;
    p->pMat = (float *)malloc(sizeof(float) * row * col);
    return p;
}

void valueInMatrix(struct Matrix *p)
{
    if (p != NULL)
    {
        float *mat = p->pMat;
        int row = p->row, col = p->col;
        float arr[row * col];
        for (int i = 0; i < row; i++)
            for (int j = 0; j < col; j++)
            {
                scanf("%f", &arr[i * col + j]);
            }
        for (int i = 0; i < row * col; i++)
            *(mat + i) = arr[i];
    }
    else
        printf("Matrix is NULL, please check!");
}

void deleteMatrix(struct Matrix *mat)
{
    if (mat->pMat != NULL)
    {
        free(mat->pMat);
        mat->pMat = NULL;
    }
    else
        printf("The matrix is NULL!");
    if (mat != NULL)
    {
        free(mat);
        mat = NULL;
    }
    else
        printf("The matrix is NULL!");
}

struct Matrix *copyMatrix(const struct Matrix *mat)
{
    if (mat != NULL)
    {
        struct Matrix *mat_copy = createMatrix(mat->row, mat->col);
        int count = mat->row * mat->col;
        float *p = mat->pMat;
        float *p_copy = mat_copy->pMat;
        for (int i = 0; i < count; i++)
        {
            *(p_copy + i) = *(p + i);
        }
        return mat_copy;
    }
    else
    {
        printf("Matrix is NULL, please check!");
        return NULL;
    }
}

struct Matrix *addMatrix(const struct Matrix *mat1, const struct Matrix *mat2)
{
    if (mat1 != NULL && mat2 != NULL)
    {
        if (mat1->row != mat2->row || mat1->col != mat2->col)
        {
            printf("Please input the right format of the addition of two matrices.");
            return NULL;
        }
        else
        {
            struct Matrix *mat = createMatrix(mat1->row, mat1->col);
            int count = mat1->row * mat1->col;
            for (int i = 0; i < count; i++)
            {
                *(mat->pMat + i) = *(mat1->pMat + i) + *(mat2->pMat + i);
            }
            return mat;
        }
    }
    else
    {
        printf("One of two input Matrices is NULL!");
        return NULL;
    }
}

struct Matrix *subtractMatrix(const struct Matrix *mat1, const struct Matrix *mat2)
{
    if (mat1 != NULL && mat2 != NULL)
    {
        if (mat1->row != mat2->row || mat1->col != mat2->col)
        {
            printf("Please input the right formula of the addition of two matrices.");
            return NULL;
        }
        else
        {
            struct Matrix *mat = createMatrix(mat1->row, mat1->col);
            int count = mat1->row * mat1->col;
            for (int i = 0; i < count; i++)
            {
                *(mat->pMat + i) = *(mat1->pMat + i) - *(mat2->pMat + i);
            }
            return mat;
        }
    }
    else
    {
        printf("One of two input Matrices is NULL!");
        return NULL;
    }
}

struct Matrix *scalarAddition(const struct Matrix *mat, const float a)
{
    if (mat != NULL)
    {
        struct Matrix *matp = createMatrix(mat->row, mat->col);
        int count = mat->row * mat->col;
        for (int i = 0; i < count; i++)
        {
            *(matp->pMat + i) = *(mat->pMat + i) + a;
        }
        return matp;
    }
    else
    {
        printf("Matrix is NULL!");
        return NULL;
    }
}

struct Matrix *scalarSubtraction(const struct Matrix *mat, const float a)
{
    if (mat != NULL)
    {
        struct Matrix *matp = createMatrix(mat->row, mat->col);
        int count = mat->row * mat->col;
        for (int i = 0; i < count; i++)
        {
            *(matp->pMat + i) = *(mat->pMat + i) - a;
        }
        return matp;
    }
    else
    {
        printf("Matrix is NULL!");
        return NULL;
    }
}

struct Matrix *scalarMultiplication(const struct Matrix *mat, const float a)
{
    if (mat != NULL)
    {
        struct Matrix *matp = createMatrix(mat->row, mat->col);
        int count = mat->row * mat->col;
        for (int i = 0; i < count; i++)
        {
            *(matp->pMat + i) = *(mat->pMat + i) * a;
        }
        return matp;
    }
    else
    {
        printf("Matrix is NULL!");
        return NULL;
    }
}

struct Matrix *MatrixMultiplication(const struct Matrix *mat1, const struct Matrix *mat2)
{
    if (mat1 != NULL && mat2 != NULL)
    {
        if (mat1->col == mat2->row)
        {
            int row = mat1->row;
            int col = mat2->col;
            float *pMat1 = mat1->pMat;
            float *pMat2 = mat2->pMat;
            struct Matrix *mat = createMatrix(row, col);
            for (int i = 0; i < mat1->row; i++)
                for (int j = 0; j < mat2->col; j++)
                {
                    float c = 0.0f;
                    for (int k = 0; k < mat1->col; k++)
                    {
                        c += *(pMat1 + i * mat1->col + k) * *(pMat2 + k * mat2->col + j);
                    }
                    *(mat->pMat + i * col + j) = c;
                }
            return mat;
        }
        else
        {
            printf("The first matrix's row is not equal to the second matrix's column.");
            return NULL;
        }
    }
    else
    {
        printf("One of the matrices is NULL！");
        return NULL;
    }
}

float minMatrix(const struct Matrix *mat)
{
    if (mat != NULL)
    {
        int count = mat->row + mat->col;
        float *pMat = mat->pMat;
        float min_value = __FLT_MAX__;
        for (int i = 0; i < count; i++)
        {
            if (*(pMat + i) < min_value)
            {
                min_value = *(pMat + i);
            }
        }
        return min_value;
    }
    else
    {
        printf("The matrix is NULL!");
        return 0;
    }
}

float maxMatrix(const struct Matrix *mat)
{
    if (mat != NULL)
    {
        int count = mat->row + mat->col;
        float *pMat = mat->pMat;
        float max_value = __FLT_MIN__;
        for (int i = 0; i < count; i++)
        {
            if (*(pMat + i) > max_value)
            {
                max_value = *(pMat + i);
            }
        }
        return max_value;
    }
    else
    {
        printf("The matrix is NULL!");
        return 0;
    }
}

void outPutMatrix(struct Matrix *mat)
{
    if (mat != NULL)
        for (int i = 0; i < mat->row; i++)
        {
            for (int j = 0; j < mat->col; j++)
                printf("%f ", *(mat->pMat + i * mat->col + j));
            printf("\n");
        }
    else
        printf("The matrix is NULL!");
}

int main()
{
    int row, col;
    scanf("%d%d", &row, &col);
    struct Matrix *m1 = createMatrix(row, col);
    valueInMatrix(m1);
    scanf("%d%d", &row, &col);
    struct Matrix *m2 = createMatrix(row, col);
    valueInMatrix(m2);
    struct Matrix *mp = MatrixMultiplication(m1, m2);
    outPutMatrix(mp);
    deleteMatrix(m1);
    deleteMatrix(m2);
    deleteMatrix(mp);
}