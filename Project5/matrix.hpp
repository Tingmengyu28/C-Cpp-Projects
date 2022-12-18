#pragma once

#include <iostream>
#include <cstring>
#include <string>

using namespace std;

template <typename T>
class Matrix
{
private:
    size_t row;
    size_t col;
    size_t channel;
    size_t row_begin;
    size_t col_begin;
    size_t roi_row; // Number of row of real matrix
    size_t roi_col; // Number of column of real matrix
    T *pMat;
    size_t *refcount;
    const char *type;

public:
    Matrix();
    Matrix(size_t row, size_t col, size_t channel);
    Matrix(const Matrix &mat);
    Matrix(const Matrix &mat, size_t row_begin, size_t col_begin, size_t roi_row, size_t roi_col);
    Matrix(size_t row, size_t col, size_t channel, size_t row_begin, size_t col_begin, size_t roi_row, size_t roi_col);
    ~Matrix();

    size_t getRow()
    {
        return roi_row;
    }
    size_t getCol()
    {
        return roi_col;
    }
    size_t getChannel()
    {
        return channel;
    }
    const char *getType()
    {
        return type;
    }
    void randomValueMatrix();

    Matrix operator=(const Matrix &mat);
    Matrix operator+(const Matrix &mat);
    Matrix operator+(const T scalar);
    Matrix operator-(const Matrix &mat);
    Matrix operator-(const T scalar);
    Matrix operator*(const Matrix &mat);
    Matrix operator*(const T scalar);
    bool operator==(const Matrix &mat);

    template <typename T1>
    friend Matrix<T1> operator+(const T1 scalar, const Matrix<T1> &mat);
    template <typename T1>
    friend Matrix<T1> operator-(const T1 scalar, const Matrix<T1> &mat);
    template <typename T1>
    friend Matrix<T1> operator*(const T1 scalar, const Matrix<T1> &mat);
    template <typename T1>
    friend ostream &operator<<(ostream &output, const Matrix<T1> &mat);
};