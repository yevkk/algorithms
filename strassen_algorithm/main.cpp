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



int main() {
    int a[] = {1, 2, 3, 4, 2, 3, 4, 5, 3, 4, 5, 6};
    int b[] = {1, 2, 3, 4, 2, 3, 4, 5, 3, 4, 5, 6};
    Matrix M1(a, 3, 4);
    Matrix M2(b, 4, 3);
    matrixMultipty(M1, M2).print();
    return 0;
}