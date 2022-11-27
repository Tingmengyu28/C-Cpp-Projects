#include <stdio.h>
#include <immintrin.h>
#include <time.h>
#include "matrix.h"

int main()
{
    clock_t start, finish;
    double duration_plain, duration_improved;
    int row, col;
    int size[5] = {16, 128, 1000, 2000};
    // int size[3] = {160, 640, 1280};
    for (int i = 0; i < sizeof(size) / 4; i++)
    {
        row = size[i];
        printf("-----New result-----\n");
        printf("Dimension : %d\n", row);
        struct Matrix *m1 = createMatrix(row, row);
        randomValueMatrix(m1);
        struct Matrix *m2 = createMatrix(row, row);
        randomValueMatrix(m2);
        start = clock();
        struct Matrix *mn = matmul_plain(m1, m2);
        finish = clock();
        duration_plain = (double)(finish - start) / CLOCKS_PER_SEC;
        printf("Normal : %f seconds\n", duration_plain);
        start = clock();
        struct Matrix *mp = matmul_improved(m1, m2);
        finish = clock();
        duration_improved = (double)(finish - start) / CLOCKS_PER_SEC;
        printf("Improved : %f seconds\n", duration_improved);
        deleteMatrix(m1);
        deleteMatrix(m2);
        deleteMatrix(mn);
        deleteMatrix(mp);
    }
}