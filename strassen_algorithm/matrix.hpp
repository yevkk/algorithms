#pragma once

#include <iostream>
#include <ctime>
#include <random>

class Matrix {
private:
    static const int _MIN_RAND_VALUE = -3;
    static const int _MAX_RAND_VALUE = 10;

    int **_elements;
public:
    int rows;
    int columns;

    Matrix(const int &size_r, const int &size_c, const int &zero_flag = 0);

    int operator()(int index_r, int index_c) const;

    int &operator()(int index_r, int index_c);

    int *operator()(int index_r) const;

    Matrix operator+(const Matrix &M) const;

    Matrix operator-(const Matrix &M) const;

    void print();
};

Matrix matrixMultiply(const Matrix &A, const Matrix &B);

Matrix matrixMultiplyRecStep(const Matrix &A, const Matrix &B, const int &size);

Matrix matrixMultiplyRec(const Matrix &A, const Matrix &B);

Matrix strassenAlgorithmStep(const Matrix &A, const Matrix &B, const int &size);

Matrix strassenAlgorithm(const Matrix &A, const Matrix &B);