#include <iostream>
#include <cstring>
#include <string>
#include "matrix.hpp"

using namespace std;

// Null Matrix constructor
template <typename T>
Matrix<T>::Matrix() : row(0), col(0), channel(0), row_begin(0), col_begin(0), roi_row(0), roi_col(0)
{
    pMat = NULL;
    refcount = NULL;
    type = typeid(T).name();
}
// Full matrix constructor
template <typename T>
Matrix<T>::Matrix(size_t row, size_t col, size_t channel) : row(row), col(col), channel(channel), row_begin(0), col_begin(0), roi_row(row), roi_col(col)
{
    pMat = new T[row * col * channel * sizeof(T)]{};
    refcount = new size_t(1);
    type = typeid(T).name();
}
// Copy Constructor
template <typename T>
Matrix<T>::Matrix(const Matrix &mat) : row(mat.row), col(mat.col), pMat(mat.pMat), type(mat.type), refcount(mat.refcount), channel(mat.channel), row_begin(mat.row_begin), col_begin(mat.col_begin)
{
    roi_row = mat.roi_row;
    roi_col = mat.roi_col;
    ++*refcount;
}
// ROI Matrix Constructor
template <typename T>
Matrix<T>::Matrix(const Matrix &mat, size_t row_begin, size_t col_begin, size_t roi_row, size_t roi_col) : row_begin(row_begin), col_begin(col_begin), roi_row(roi_row), roi_col(roi_col)
{
    row = mat.row;
    col = mat.col;
    pMat = mat.pMat;
    type = mat.type;
    refcount = mat.refcount;
    ++*refcount;
    channel = mat.channel;
}
template <typename T>
Matrix<T>::Matrix(size_t row, size_t col, size_t channel, size_t row_begin, size_t col_begin, size_t roi_row, size_t roi_col) : row(row), col(col), channel(channel), row_begin(row_begin), col_begin(col_begin), roi_row(roi_row), roi_col(roi_col)
{
    pMat = new T[row * col * channel * sizeof(T)]{};
    refcount = new size_t(1);
    type = typeid(T).name();
}
// Deconstructor
template <typename T>
Matrix<T>::~Matrix()
{
    if (*refcount > 1)
    {
        --*refcount;
        pMat = NULL;
    }
    else if (*refcount == 1)
    {
        delete pMat;
        delete refcount;
        pMat = NULL;
        refcount = NULL;
    }
    else
    {
        cout << "Pointer does not point to any matrix!" << endl;
    }
}
template <typename T>
void Matrix<T>::randomValueMatrix()
{
    for (size_t i = 0; i < row * col * channel; i++)
        *(pMat + i) = rand() % 10;
}

template <typename T>
bool Matrix<T>::operator==(const Matrix &mat)
{
    try
    {
        if (!strcmp(type, mat.type))
        {
            if (roi_row == mat.roi_row && roi_col == mat.roi_col && channel == mat.channel)
            {
                for (size_t ch = 0; ch < channel; ch++)
                {
                    for (size_t i = 0; i < roi_row; i++)
                    {
                        for (size_t j = 0; j < roi_col; j++)
                        {
                            if (*(pMat + (row_begin + i) * col + col_begin + j + ch * row * col) != *(mat.pMat + (mat.row_begin + i) * mat.col + mat.col_begin + j + ch * mat.row * mat.col))
                                throw "Error : These two matrices are not equal!";
                        }
                    }
                }
                return 1;
            }
            else
            {
                throw "Error : The shape of two matrices are different!";
            }
        }
        else
        {
            throw "Error : The type of the two matrices are different!";
        }
    }
    catch(const char* msg)
    {
        cerr << msg << endl;
    }
    return 0;
}
template <typename T>
Matrix<T> Matrix<T>::operator=(const Matrix<T> &mat)
{
    try
    {
        if (!strcmp(type, mat.type))
        {
            row = mat.row;
            col = mat.col;
            row_begin = mat.row_begin;
            col_begin = mat.col_begin;
            roi_row = mat.roi_row;
            roi_col = mat.roi_col;
            channel = mat.channel;
            if (refcount != NULL)
            {
                if (mat.refcount == NULL)
                {
                    if (--*refcount == 0)
                    {
                        delete pMat;
                        delete refcount;
                    }
                    pMat = NULL;
                    refcount = NULL;
                }
                else
                {
                    ++*mat.refcount;
                    if (--*refcount == 0)
                    {
                        delete pMat;
                        delete refcount;
                    }
                    pMat = mat.pMat;
                    refcount = mat.refcount;
                }
            }
            else
            {
                if (mat.refcount != NULL)
                {
                    ++*mat.refcount;
                    pMat = mat.pMat;
                    refcount = mat.refcount;
                }
            }
            return *this;
        }
        else
        {
            throw "Error : The type of the two matrices are different!";
        }
    }
    catch (const char *msg)
    {
        cerr << msg << endl;
    }
    return *this;
}
template <typename T>
Matrix<T> Matrix<T>::operator+(const Matrix<T> &mat)
{
    try
    {
        if (!strcmp(type, mat.type))
        {
            if (refcount != NULL && mat.refcount != NULL)
            {
                if (roi_row != mat.roi_row || roi_col != mat.roi_col || channel != mat.channel)
                {
                    throw "Error : The shape of two matrices are not same!";
                }
                else
                {
                    Matrix new_mat(roi_row, roi_col, channel);
                    for (size_t ch = 0; ch < channel; ch++)
                        for (size_t i = 0; i < roi_row; i++)
                            for (size_t j = 0; j < roi_col; j++)
                            {
                                *(new_mat.pMat + i * roi_col + j + ch * roi_row * roi_col) = 
                                *(pMat + col * (row_begin + i) + col_begin + j + ch * row * col) + 
                                *(mat.pMat + mat.col * (mat.row_begin + i) + mat.col_begin + j + ch * mat.row * mat.col);
                            }
                    return new_mat;
                }
            }
            else
            {
                throw "Error : One of the matrix is empty matrix!";
            }
        }
        else
        {
            throw "Error : The type of two matrices are different!";
        }
    }
    catch(const char* msg)
    {
        cerr << msg << endl;
    }
    Matrix null_mat;
    return null_mat;
}
template <typename T>
Matrix<T> Matrix<T>::operator+(const T scalar)
{
    try
    {
        if (!strcmp(type, typeid(T).name()))
        {
            if (refcount != NULL)
            {
                Matrix new_mat(roi_row, roi_col, channel);
                for (size_t ch = 0; ch < channel; ch++)
                    for (size_t i = 0; i < roi_row; i++)
                        for (size_t j = 0; j < roi_col; j++)
                        {
                            *(new_mat.pMat + i * roi_col + j + ch * roi_row * roi_col) =
                                *(pMat + col * (row_begin + i) + col_begin + j + ch * row * col) + scalar;
                        }
                return new_mat;
            }
            else
            {
                throw "Error : The matrix is empty matrix!";
            }
        }
        else
        {
            throw "Error : The type of scalar is different from matrix!";
        }
    }
    catch(const char* msg)
    {
        cerr << msg << endl;
    }
    Matrix null_mat;
    return null_mat;
}
template <typename T1>
Matrix<T1> operator+(const T1 scalar, const Matrix<T1> &mat)
{
    try
    {
        if (!strcmp(typeid(T1).name(), mat.type))
        {
            size_t row = mat.row, col = mat.col;
            T1 *pMat = mat.pMat;
            if (mat.refcount != NULL)
            {
                Matrix<T1> new_mat(mat.roi_row, mat.roi_col, mat.channel);
                for (size_t ch = 0; ch < mat.channel; ch++)
                    for (size_t i = 0; i < mat.roi_row; i++)
                        for (size_t j = 0; j < mat.roi_col; j++)
                        {
                            *(new_mat.pMat + i * mat.roi_col + j + ch * mat.roi_row * mat.roi_col) =
                                *(pMat + col * (mat.row_begin + i) + mat.col_begin + j + ch * row * col) + scalar;
                        }
                return new_mat;
            }
            else
            {
                throw "Error : The matrix is empty matrix!";
            }
        }
        else
        {
            throw "Error : The type of scalar is different from matrix!";
        }
    }
    catch (const char *msg)
    {
        cerr << msg << endl;
    }
    Matrix<T1> null_mat;
    return null_mat;
}
template <typename T>
Matrix<T> Matrix<T>::operator-(const Matrix<T> &mat)
{
    try
    {
        if (!strcmp(type, mat.type))
        {
            if (refcount != NULL && mat.refcount != NULL)
            {
                if (roi_row != mat.roi_row || roi_col != mat.roi_col || channel != mat.channel)
                {
                    throw "Error : The shape of two matrices are not same!";
                }
                else
                {
                    Matrix new_mat(roi_row, roi_col, channel);
                    for (size_t ch = 0; ch < channel; ch++)
                        for (size_t i = 0; i < roi_row; i++)
                            for (size_t j = 0; j < roi_col; j++)
                            {
                                *(new_mat.pMat + i * roi_col + j + ch * roi_row * roi_col) =
                                    *(pMat + col * (row_begin + i) + col_begin + j + ch * row * col) -
                                    *(mat.pMat + mat.col * (mat.row_begin + i) + mat.col_begin + j + ch * mat.row * mat.col);
                            }
                    return new_mat;
                }
            }
            else
            {
                throw "Error : One of the matrix is empty matrix!";
            }
        }
        else
        {
            throw "Error : The type of two matrices are different!";
        }
    }
    catch (const char *msg)
    {
        cerr << msg << endl;
    }
    Matrix null_mat;
    return null_mat;
}
template <typename T>
Matrix<T> Matrix<T>::operator-(const T scalar)
{
    try
    {
        if (!strcmp(type, typeid(T).name()))
        {
            if (refcount != NULL)
            {
                Matrix new_mat(roi_row, roi_col, channel);
                for (size_t ch = 0; ch < channel; ch++)
                    for (size_t i = 0; i < roi_row; i++)
                        for (size_t j = 0; j < roi_col; j++)
                        {
                            *(new_mat.pMat + i * roi_col + j + ch * roi_row * roi_col) =
                                *(pMat + col * (row_begin + i) + col_begin + j + ch * row * col) - scalar;
                        }
                return new_mat;
            }
            else
            {
                throw "Error : The matrix is empty matrix!";
            }
        }
        else
        {
            throw "Error : The type of scalar is different from matrix!";
        }
    }
    catch (const char *msg)
    {
        cerr << msg << endl;
    }
    Matrix null_mat;
    return null_mat;
}
template <typename T1>
Matrix<T1> operator-(const T1 scalar, const Matrix<T1> &mat)
{
    try
    {
        if (!strcmp(typeid(T1).name(), mat.type))
        {
            size_t row = mat.row, col = mat.col;
            T1 *pMat = mat.pMat;
            if (mat.refcount != NULL)
            {
                Matrix<T1> new_mat(mat.roi_row, mat.roi_col, mat.channel);
                for (size_t ch = 0; ch < mat.channel; ch++)
                    for (size_t i = 0; i < mat.roi_row; i++)
                        for (size_t j = 0; j < mat.roi_col; j++)
                        {
                            *(new_mat.pMat + i * mat.roi_col + j + ch * mat.roi_row * mat.roi_col) =
                                -*(pMat + col * (mat.row_begin + i) + mat.col_begin + j + ch * row * col) + scalar;
                        }
                return new_mat;
            }
            else
            {
                throw "Error : The matrix is empty matrix!";
            }
        }
        else
        {
            throw "Error : The type of scalar is different from matrix!";
        }
    }
    catch (const char *msg)
    {
        cerr << msg << endl;
    }
    Matrix<T1> null_mat;
    return null_mat;
}
template <typename T>
Matrix<T> Matrix<T>::operator*(const Matrix<T> &mat)
{
    try
    {
        if (!strcmp(type, mat.type))
        {
            if (refcount != NULL && mat.refcount != NULL)
            {
                if (roi_col != mat.roi_row || channel != mat.channel)
                {
                    throw "Error : Illegal multiplication!";
                }
                else
                {
                    Matrix<T> new_mat(roi_row, mat.roi_col, channel);
                    float c;
                    for (size_t ch = 0; ch < channel; ch++)
                        for (size_t i = 0; i < roi_row; i++)
                            for (size_t j = 0; j < mat.roi_col; j++)
                            {
                                c = 0.f;
                                for (size_t k = 0; k < roi_col; k++)
                                {
                                    c += *(pMat + (i + row_begin) * col + k + col_begin + ch * row * col) * *(mat.pMat + (k + mat.row_begin) * mat.col + j + mat.col_begin + ch * mat.row * mat.col);
                                }
                                *(new_mat.pMat + i * new_mat.col + j + ch * roi_row * roi_col) = c;
                            }
                    return new_mat;
                }
            }
            else
            {
                throw "Error : One of the matrix is empty matrix!";
            }
        }
        else
        {
            throw "Error : The type of two matrices are different!";
        }
    }
    catch (const char *msg)
    {
        cerr << msg << endl;
    }
    Matrix null_mat;
    return null_mat;
}
template <typename T>
Matrix<T> Matrix<T>::operator*(const T scalar)
{
    try
    {
        if (!strcmp(type, typeid(T).name()))
        {
            if (refcount != NULL)
            {
                Matrix new_mat(roi_row, roi_col, channel);
                for (size_t ch = 0; ch < channel; ch++)
                    for (size_t i = 0; i < roi_row; i++)
                        for (size_t j = 0; j < roi_col; j++)
                        {
                            *(new_mat.pMat + i * roi_col + j + ch * roi_row * roi_col) =
                                *(pMat + col * (row_begin + i) + col_begin + j + ch * row * col) * scalar;
                        }
                return new_mat;
            }
            else
            {
                throw "Error : The matrix is empty matrix!";
            }
        }
        else
        {
            throw "Error : The type of scalar is different from matrix!";
        }
    }
    catch (const char *msg)
    {
        cerr << msg << endl;
    }
    Matrix null_mat;
    return null_mat;
}
template <typename T1>
Matrix<T1> operator*(const T1 scalar, const Matrix<T1> &mat)
{
    try
    {
        if (!strcmp(typeid(T1).name(), mat.type))
        {
            size_t row = mat.row, col = mat.col;
            T1 *pMat = mat.pMat;
            if (mat.refcount != NULL)
            {
                Matrix<T1> new_mat(mat.roi_row, mat.roi_col, mat.channel);
                for (size_t ch = 0; ch < mat.channel; ch++)
                    for (size_t i = 0; i < mat.roi_row; i++)
                        for (size_t j = 0; j < mat.roi_col; j++)
                        {
                            *(new_mat.pMat + i * mat.roi_col + j + ch * mat.roi_row * mat.roi_col) =
                                *(pMat + col * (mat.row_begin + i) + mat.col_begin + j + ch * row * col) * scalar;
                        }
                return new_mat;
            }
            else
            {
                throw "Error : The matrix is empty matrix!";
            }
        }
        else
        {
            throw "Error : The type of scalar is different from matrix!";
        }
    }
    catch (const char *msg)
    {
        cerr << msg << endl;
    }
    Matrix<T1> null_mat;
    return null_mat;
}

template <typename T1>
ostream &operator<<(ostream &output, const Matrix<T1> &mat)
{
    output << "------Matrix------" << endl;
    if (mat.pMat != NULL)
    {
        for (size_t ch = 0; ch < mat.channel; ch++)
        {
            output << "Channel : " << (ch + 1) << endl;
            for (size_t i = 0; i < mat.roi_row; i++)
            {
                for (size_t j = 0; j < mat.roi_col; j++)
                {
                    output << *(mat.pMat + (mat.row_begin + i) * mat.col + mat.col_begin + j + ch * mat.row * mat.col) << " ";
                }
                output << endl;
            }
        }
        return output;
    }
    else
    {
        output << "Empty Matrix" << endl;
        return output;
    }
}

template class Matrix<float>;
int main()
{
    Matrix<float> mat(4, 3, 2);
    // Matrix<float> mat2(mat, 0, 0, 2, 2);
    Matrix<float> mat2(mat, 0, 0, 2, 2);
    Matrix<float> mat3(mat, 0, 0, 2, 2);
    mat.randomValueMatrix();
    // mat2.randomValueMatrix();
    cout << mat2;
    cout << mat3;
    cout << (mat2 == mat3);
}