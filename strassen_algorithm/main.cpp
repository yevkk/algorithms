#include <iostream>
#include <ctime>
#include <random>

int rand_int(int min, int max) {
    static std::random_device rd;
    static std::seed_seq seed{rd(), static_cast<unsigned int>(time(nullptr))};
    static std::mt19937_64 gen(seed);
    std::uniform_int_distribution<int> dist(min, max);

    return dist(gen);
}

class Matrix {
private:
    const int _MIN_RAND_VALUE = 0;
    const int _MAX_RAND_VALUE = 10;
public:
    struct {
        int rows;
        int columns;
    } size = {};

    int **elements;

    Matrix(int *array, const int &size_r, const int &size_c) {
        elements = new int *[size_r];
        for (int i = 0; i < size_r; i++) {
            elements[i] = new int[size_c];
            std::copy(array + i * size_c, array + i * size_c + size_r + 1, elements[i]);
        }
        size = {size_r, size_c};
    }

    Matrix(const int &size_r, const int &size_c, const int &zero_flag = 0) {
        elements = new int *[size_r];
        for (int i = 0; i < size_r; i++) {
            elements[i] = new int[size_c];
            for (int j = 0; j < size_c; j++)
                elements[i][j] = (zero_flag) ? 0 : rand_int(_MIN_RAND_VALUE, _MAX_RAND_VALUE);
        }
        size = {size_r, size_c};
    }

    ~Matrix() {
        for (int i = 0; i < size.rows; i++)
            delete[] elements[i];
        delete &size;
    }

    Matrix operator+(const Matrix &M) {
        if ((this->size.rows != M.size.rows) || (this->size.columns != M.size.columns))
            return *(this);

        Matrix res(this->size.rows, this->size.columns, true);
        for (int i = 0; i < this->size.rows; i++)
            for (int j = 0; j < this->size.columns; j++)
                res.elements[i][j] = this->elements[i][j] + M.elements[i][j];

        return res;
    }

    Matrix operator-(const Matrix &M) {
        if ((this->size.rows != M.size.rows) || (this->size.columns != M.size.columns))
            return *(this);

        Matrix res(this->size.rows, this->size.columns, true);
        for (int i = 0; i < this->size.rows; i++)
            for (int j = 0; j < this->size.columns; j++)
                res.elements[i][j] = this->elements[i][j] - M.elements[i][j];

        return res;
    }

    void print() {
        for (int i = 0; i < size.rows; i++) {
            std::cout << i << ") ";
            for (int j = 0; j < size.columns; j++) {
                std::cout << elements[i][j] << ' ';
            }
            std::cout << std::endl;
        }
    }
};

Matrix matrixMultipty(const Matrix &A, const Matrix &B) {
    if ((A.size.rows != B.size.columns) || (A.size.columns != B.size.rows))
        return A;

    Matrix C(A.size.rows, B.size.columns, true);
    for (int i = 0; i < A.size.rows; i++)
        for (int j = 0; j < B.size.columns; j++)
            for (int k = 0; k < A.size.columns; k++)
                C.elements[i][j] += A.elements[i][k] * B.elements[k][j];
    return C;
}

Matrix strassenAlgorithmStep(const Matrix &A, const Matrix &B, const int &size) {
    if (size == 2) return matrixMultipty(A, B);

    Matrix A11(size / 2, size / 2, true);
    Matrix A12(size / 2, size / 2, true);
    Matrix A21(size / 2, size / 2, true);
    Matrix A22(size / 2, size / 2, true);
    Matrix B11(size / 2, size / 2, true);
    Matrix B12(size / 2, size / 2, true);
    Matrix B21(size / 2, size / 2, true);
    Matrix B22(size / 2, size / 2, true);

    for (int i = 0; i < size / 2; i++) {
        for (int j = 0; j < size / 2; j++) {
            A11.elements[i][j] = A.elements[i][j];
            A12.elements[i][j] = A.elements[i][j + size / 2];
            A21.elements[i][j] = A.elements[i + size / 2][j];
            A22.elements[i][j] = A.elements[i + size / 2][j + size / 2];

            B11.elements[i][j] = B.elements[i][j];
            B12.elements[i][j] = B.elements[i][j + size / 2];
            B21.elements[i][j] = B.elements[i + size / 2][j];
            B22.elements[i][j] = B.elements[i + size / 2][j + size / 2];
        }
    }

    Matrix P = strassenAlgorithmStep(A11 + A22, B11 + B22, size / 2);
    Matrix Q = strassenAlgorithmStep(A21 + A22, B11, size / 2);
    Matrix R = strassenAlgorithmStep(A11, B12 - B22, size / 2);
    Matrix S = strassenAlgorithmStep(A22, B21 - B11, size / 2);
    Matrix T = strassenAlgorithmStep(A11 + A12, B22, size / 2);
    Matrix U = strassenAlgorithmStep(A21 - A11, B11 + B12, size / 2);
    Matrix V = strassenAlgorithmStep(A12 - A22, B21 + B22, size / 2);

    Matrix C11 = P + S - T + V;
    Matrix C12 = R + T;
    Matrix C21 = Q + S;
    Matrix C22 = P + R - Q + U;

    Matrix C(size, size, true);

    for (int i = 0; i < size / 2; i++) {
        for (int j = 0; j < size / 2; j++) {
            C.elements[i][j] = C11.elements[i][j];
            C.elements[i][j + size / 2] = C12.elements[i][j];
            C.elements[i + size / 2][j] = C21.elements[i][j];
            C.elements[i + size / 2][j + size / 2] = C22.elements[i][j];
        }
    }

    return C;
}

Matrix strassenAlgorithm(const Matrix &A, const Matrix &B) {
    if ((A.size.rows != B.size.columns) || (A.size.columns != B.size.rows))
        return A;
    int new_size = 1, curr_size = (A.size.rows < A.size.columns) ? A.size.columns : A.size.rows;
    while (new_size < curr_size)
        new_size *= 2;

    Matrix new_A(new_size, new_size, true);
    Matrix new_B(new_size, new_size, true);

    for (int i = 0; i < A.size.rows; i++)
        std::copy(A.elements[i] + 0, A.elements[i] + A.size.columns, new_A.elements[i]);

    for (int i = 0; i < B.size.rows; i++)
        std::copy(B.elements[i] + 0, B.elements[i] + B.size.columns, new_B.elements[i]);

    return strassenAlgorithmStep(new_A, new_B, new_size);
}

int main() {
    int a[] = {1, 2, 3, 4, 2, 3, 4, 5, 3, 4, 5, 6};
    int b[] = {1, 2, 3, 4, 2, 3, 4, 5, 3, 4, 5, 6};
    Matrix M1(a, 3, 4);
    Matrix M2(b, 4, 3);
    matrixMultipty(M1, M2).print();
    std::cout << std::endl;
    strassenAlgorithm(M1, M2).print();
    return 0;
}