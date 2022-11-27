#include <stdio.h>
#include <stdlib.h>
#include <immintrin.h>
#include <omp.h>
#include <stdlib.h>
#include <time.h>
#include "matrix.h"

struct Matrix *createMatrix(int row, int col)
{
    if (row > 0 && col > 0)
    {
        struct Matrix *p = (struct Matrix *)malloc(sizeof(struct Matrix));
        p->row = (size_t)row;
        p->col = (size_t)col;
        p->pMat = (float *)malloc(sizeof(float) * row * col);
        return p;
    }
    else
    {
        printf("Please input two positive integers!");
        return NULL;
    }
}

void valueInMatrix(struct Matrix *p)
{
    if (p != NULL)
    {
        float *mat = p->pMat;
        size_t row = p->row, col = p->col;
        float arr[row * col];
        for (size_t i = 0; i < row; i++)
            for (size_t j = 0; j < col; j++)
            {
                scanf("%f", &arr[i * col + j]);
            }
        for (size_t i = 0; i < row * col; i++)
            *(mat + i) = arr[i];
    }
    else
        printf("Matrix is NULL, please check!");
}

void randomValueMatrix(struct Matrix *p)
{
    if (p != NULL)
    {
        float *mat = p->pMat;
        size_t row = p->row, col = p->col;
        for (size_t i = 0; i < row * col; i++)
            *(mat + i) = rand() % 10;
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
        size_t count = mat->row * mat->col;
        float *p = mat->pMat;
        float *p_copy = mat_copy->pMat;
        for (size_t i = 0; i < count; i++)
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
            size_t count = mat1->row * mat1->col;
            for (size_t i = 0; i < count; i++)
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
            size_t count = mat1->row * mat1->col;
            for (size_t i = 0; i < count; i++)
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
        size_t count = mat->row * mat->col;
        for (size_t i = 0; i < count; i++)
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
        size_t count = mat->row * mat->col;
        for (size_t i = 0; i < count; i++)
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
        size_t count = mat->row * mat->col;
        for (size_t i = 0; i < count; i++)
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

struct Matrix *matmul_plain(const struct Matrix *mat1, const struct Matrix *mat2)
{
    if (mat1 != NULL && mat2 != NULL)
    {
        if (mat1->col == mat2->row)
        {
            size_t row = mat1->row;
            size_t col = mat2->col;
            float *pMat1 = mat1->pMat;
            float *pMat2 = mat2->pMat;
            struct Matrix *mat = createMatrix(row, col);
            for (size_t i = 0; i < row; i++)
                for (size_t j = 0; j < col; j++)
                {
                    float c = 0.0f;
                    for (size_t k = 0; k < mat1->col; k++)
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

float sum(struct Matrix *mat)
{
    float n = 0.f;
    float *arr = mat->pMat;
    for (size_t i = 0; i < sizeof(arr) / 4; i++)
    {
        n += *(arr + i);
    }
    return n;
}

struct Matrix *matmul_improved(const struct Matrix *mat1, const struct Matrix *mat2)
{
    if (mat1 != NULL && mat2 != NULL)
    {
        if (mat1->col == mat2->row)
        {
            size_t row = mat1->row;
            size_t col = mat2->col;
            size_t n = mat1->col;
            float *pMat1 = mat1->pMat;
            float *pMat2 = mat2->pMat;
            struct Matrix *mat = createMatrix(row, col);
            float *sum = (float *)malloc(8 * sizeof(float));
            for (int i = 0; i < 8; i++)
                sum[i] = 0;
            __m256 a, b;
            float *pMat2_t = (float *)malloc(mat2->row * mat2->col * sizeof(float));
            for (size_t i = 0; i < mat2->col; i++)
            {
                for (size_t j = 0; j < mat2->row; j++)
                {
                    *(pMat2_t + i * mat2->row + j) = *(pMat2 + j * mat2->col + i);
                }
            }
#pragma omp parallel for
            for (size_t i = 0; i < mat1->row; i++)
            {
                for (size_t j = 0; j < mat2->col; j++)
                {
                    if (mat1->col % 8 == 0)
                    {
                        __m256 c = _mm256_setzero_ps();
                        for (size_t k = 0; k < mat1->col; k += 8)
                        {
                            a = _mm256_loadu_ps(pMat1 + i * mat1->col + k);
                            b = _mm256_loadu_ps(pMat2_t + j * mat2->row + k);
                            c = _mm256_add_ps(c, _mm256_mul_ps(a, b));
                        }
                        _mm256_storeu_ps(sum, c);
                        float *mat_arr = mat->pMat;
                        *(mat_arr + i * col + j) = sum[0] + sum[1] + sum[2] + sum[3] + sum[4] + sum[5] + sum[6] + sum[7];
                    }
                    else
                    {
                        size_t times = mat1->col / 8;
                        size_t k = 0;
                        __m256 c = _mm256_setzero_ps();
                        for (size_t t = 0; t < times; t++)
                        {
                            a = _mm256_loadu_ps(pMat1 + i * mat1->col + k);
                            b = _mm256_loadu_ps(pMat2_t + j * mat2->row + k);
                            c = _mm256_add_ps(c, _mm256_mul_ps(a, b));
                            k += 8;
                        }
                        _mm256_storeu_ps(sum, c);
                        float *mat_arr = mat->pMat;
                        *(mat_arr + i * col + j) = sum[0] + sum[1] + sum[2] + sum[3] + sum[4] + sum[5] + sum[6] + sum[7];
                        for (int k = 8 * times; k < mat1->col; k++)
                            *(mat_arr + i * col + j) += *(pMat1 + i * mat1->col + k) * *(pMat2 + k * mat2->col + j);
                    }
                }
            }
            free(pMat2_t);
            free(sum);
            return mat;
        }
        else
        {
            printf("The first matrix's row is not equal to the second matrix's column.");
            return 0;
        }
    }
    else
    {
        printf("One of the matrices is NULL！");
        return 0;
    }
}

// struct Matrix *matmul_improved_strassen(const struct Matrix *mat1, const struct Matrix *mat2)
// {
//     if (mat1 != NULL && mat2 != NULL)
//     {
//         if (mat1->col == mat2->row)
//         {
//             size_t row = mat1->row;
//             size_t col = mat2->col;
//             size_t n = mat1->col;
//             float *pMat1 = mat1->pMat;
//             float *pMat2 = mat2->pMat;
//             struct Matrix *mat = strassen_mul(mat1, mat2);
//             return mat;
//         }
//         else
//         {
//             printf("The first matrix's row is not equal to the second matrix's column.");
//             return 0;
//         }
//     }
//     else
//     {
//         printf("One of the matrices is NULL！");
//         return 0;
//     }
// }

// struct Matrix *strassen_mul(const struct Matrix *A, const struct Matrix *B)
// {
//     struct Matrix *C;
//     if (A->row <= 500 && A->col <= 500 && B->row <= 500 && B->col <= 500)
//     {
//         C = matmul_improved(A, B);
//     }
//     else
//     {
//         struct Matrix *A11 = divide_matrix(A, 1, 1);
//         struct Matrix *A12 = divide_matrix(A, 1, 2);
//         struct Matrix *A21 = divide_matrix(A, 2, 1);
//         struct Matrix *A22 = divide_matrix(A, 2, 2);
//         struct Matrix *B11 = divide_matrix(B, 1, 1);
//         struct Matrix *B12 = divide_matrix(B, 1, 2);
//         struct Matrix *B21 = divide_matrix(B, 2, 1);
//         struct Matrix *B22 = divide_matrix(B, 2, 2);
//         struct Matirx *S1 = subtractMatrix(B12, B22);
//         struct Matirx *S2 = addMatrix(A11, A12);
//         struct Matirx *S3 = addMatrix(A21, A22);
//         struct Matirx *S4 = subtractMatrix(B21, B11);
//         struct Matirx *S5 = addMatrix(A11, A22);
//         struct Matirx *S6 = addMatrix(B11, B22);
//         struct Matirx *S7 = subtractMatrix(A12, A22);
//         struct Matirx *S8 = addMatrix(B21, B22);
//         struct Matirx *S9 = subtractMatrix(A11, A21);
//         struct Matirx *S10 = addMatrix(B11, B12);
//     }
// }

// struct Matrix *divide_matrix(const struct Matrix *A, int num1, int num2)
// {
//     size_t nrow = A->row, ncol = A->col;
//     float *arr = A->pMat;
//     size_t left = nrow / 2, right;
//     size_t up = ncol / 2, down;
//     if (nrow % 2 == 0)
//         right = left;
//     else
//         right = left + 1;
//     if (ncol % 2 == 0)
//         down = up;
//     else
//         down = up + 1;
//     if (num1 == 1 && num2 == 1)
//     {
//         struct Matrix *subA = createMatrix(up, left);
//         float *subarr = subA->pMat;
//         for (size_t i = 0; i < left; i++)
//         {
//             for (size_t j = 0; j < up; j++)
//             {
//                 *(subarr + i * left + j) = *(arr + i * ncol + j);
//             }
//         }
//         return subA;
//     }
//     else if (num1 == 1 && num2 == 2)
//     {
//         struct Matrix *subA = createMatrix(up, right);
//         float *subarr = subA->pMat;
//         for (size_t i = 0; i < up; i++)
//         {
//             for (size_t j = left; j < ncol; j++)
//             {
//                 *(subarr + i * right + j - left) = *(arr + i * ncol + j);
//             }
//         }
//         return subA;
//     }
//     else if (num1 == 2 && num2 == 1)
//     {
//         struct Matrix *subA = createMatrix(down, left);
//         float *subarr = subA->pMat;
//         for (size_t i = up; i < nrow; i++)
//         {
//             for (size_t j = 0; j < left; j++)
//             {
//                 *(subarr + (i - up) * left + j) = *(arr + i * ncol + j);
//             }
//         }
//         return subA;
//     }
//     else if (num1 == 2 && num2 == 2)
//     {
//         struct Matrix *subA = createMatrix(down, right);
//         float *subarr = subA->pMat;
//         for (size_t i = up; i < nrow; i++)
//         {
//             for (size_t j = left; j < ncol; j++)
//             {
//                 *(subarr + (i - up) * right + j - left) = *(arr + i * ncol + j);
//             }
//         }
//         return subA;
//     }
// }

float minMatrix(const struct Matrix *mat)
{
    if (mat != NULL)
    {
        size_t count = mat->row + mat->col;
        float *pMat = mat->pMat;
        float min_value = __FLT_MAX__;
        for (size_t i = 0; i < count; i++)
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
        size_t count = mat->row + mat->col;
        float *pMat = mat->pMat;
        float max_value = __FLT_MIN__;
        for (size_t i = 0; i < count; i++)
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
        if (mat->pMat != NULL)
        {
            for (size_t i = 0; i < mat->row; i++)
            {
                for (size_t j = 0; j < mat->col; j++)
                    printf("%f ", *(mat->pMat + i * mat->col + j));
                printf("\n");
            }
        }
        else
        {
            printf("The matrix has no content!");
        }
    else
        printf("The matrix is NULL!");
}
