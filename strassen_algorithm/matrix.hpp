#pragma once

#include <iostream>
#include <ctime>
#include <random>

class Matrix {
private:
    const int _MIN_RAND_VALUE = -3;
    const int _MAX_RAND_VALUE = 10;
public:
    struct {
        int rows;
        int columns;
    } size;

    int **elements;

    Matrix(const int &size_r, const int &size_c, const int &zero_flag = 0);

    Matrix operator+(const Matrix &M);

    Matrix operator-(const Matrix &M);

    void print();
};

Matrix matrixMultipty(const Matrix &A, const Matrix &B);

Matrix strassenAlgorithmStep(const Matrix &A, const Matrix &B, const int &size);

Matrix strassenAlgorithm(const Matrix &A, const Matrix &B);