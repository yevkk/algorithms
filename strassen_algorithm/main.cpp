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

    Matrix(const int &size_r, const int &size_c, const int &zero_flag = 0) {
        elements = new int *[size_r];
        for (int i = 0; i < size_r; i++) {
            elements[i] = new int[size_c];
            for (int j = 0; j < size_c; j++)
                elements[i][j] = (zero_flag) ? 0 : rand_int(_MIN_RAND_VALUE, _MAX_RAND_VALUE);
        }
        size = {size_r, size_c};
    }

    Matrix operator+(const Matrix &M) {
        Matrix res(this->size.rows, this->size.columns, true);

        if ((this->size.rows != M.size.rows) || (this->size.columns != M.size.columns))
            return *(this);

        for (int i = 0; i < this->size.rows; i++)
            for (int j = 0; j < this->size.columns; j++)
                res.elements[i][j] = this->elements[i][j] + M.elements[i][j];

        return res;
    }

    Matrix operator-(const Matrix &M) {
        Matrix res(this->size.rows, this->size.columns, true);

        if ((this->size.rows != M.size.rows) || (this->size.columns != M.size.columns))
            return *(this);

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
    Matrix C(A.size.rows, B.size.columns, true);

    if ((A.size.rows != B.size.columns) || (A.size.columns != B.size.rows))
        return A;

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
        std::copy(A.elements[i] + 0, A.elements[i] + size / 2 + 1, A11.elements[i]);
        std::copy(A.elements[i] + size / 2, A.elements[i] + size + 1, A12.elements[i]);
        std::copy(A.elements[i + size / 2], A.elements[i + size / 2] + size / 2 + 1, A21.elements[i]);
        std::copy(A.elements[i + size / 2] + size / 2, A.elements[i + size / 2] + size + 1, A22.elements[i]);

        std::copy(B.elements[i] + 0, B.elements[i] + size / 2 + 1, B11.elements[i]);
        std::copy(B.elements[i] + size / 2, B.elements[i] + size + 1, B12.elements[i]);
        std::copy(B.elements[i + size / 2], B.elements[i + size / 2] + size / 2 + 1, B21.elements[i]);
        std::copy(B.elements[i + size / 2] + size / 2, B.elements[i + size / 2] + size + 1, B22.elements[i]);
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
        std::copy(C11.elements[i] + 0, C11.elements[i] + size / 2 + 1, C.elements[i]);
        std::copy(C12.elements[i] + 0, C12.elements[i] + size / 2 + 1, C.elements[i] + size / 2);
        std::copy(C21.elements[i] + 0, C21.elements[i] + size / 2 + 1, C.elements[i + size / 2]);
        std::copy(C22.elements[i] + 0, C22.elements[i] + size / 2 + 1, C.elements[i + size / 2] + size / 2);
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
    Matrix M1(3, 4);
    Matrix M2(4, 3);
    M1.print();
    M2.print();
    Matrix M3 = strassenAlgorithm(M1, M2);
    M3.print();
    std::cout << std::endl;
    return 0;
}