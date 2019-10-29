#pragma once

#include "matrix.hpp"
#include <cmath>

int for_hash(char c) {
    return c - 'a' + 1;
}

int for_hash(int c) {
    return c;
}

int mod(int num1, int num2) {
    return ((num1 % num2) >= 0) ? (num1 % num2) : ((num1 % num2) + num2);
}

template<typename T>
int D(){
    return 0;
};

template<>
int D<int>(){
    return 10;
};

template<>
int D<char>(){
    return 26;
};

const int Q = 23;


template<typename T>
bool matrix_match(Matrix<T> M, int r_index, int c_index, Matrix<T> P) {
    if ((c_index > M.size - P.size + 1) || (r_index > M.size - P.size + 1)) return false;
    for (int i = 0; i < P.size; ++i)
        for (int j = 0; j < P.size; ++j)
            if (M(r_index + i, c_index + j) != P(i, j)) return false;
    return true;
}

template<typename T>
int rabin_karp_extended(Matrix<T> M, Matrix<T> P) {
    int res = 0;
    if (P.size > M.size) return 0;
    Matrix<int> c_hashes(M.size);

    int p_hash = 0;
    std::vector<int> tmp_hash;;
    for (int i = 0; i < P.size; ++i) {
        tmp_hash.push_back(0);
        for (int j = 0; j < P.size; ++j) {
            tmp_hash[i] = mod(tmp_hash[i] * D<T>() + for_hash(P(j, i)), Q);
        }
    }

    for (int i = 0; i < P.size; ++i) {
        p_hash = mod(p_hash * D<T>() + for_hash(tmp_hash[i]), Q);
    }

    int h = (int) pow(D<T>(), P.size - 1) % Q;
    for (int i = 0; i < c_hashes.size; ++i) {
        for (int j = 0; j < P.size; ++j) {
            c_hashes(0, i) = mod(c_hashes(0, i) * D<T>() + for_hash(M(j, i)), Q);
        }
        for (int j = 1; j < (c_hashes.size - P.size + 1); ++j) {
            c_hashes(j, i) =
                    mod(D<T>() * (c_hashes(j - 1, i) - for_hash(M(j - 1, i)) * h) + for_hash(M(j + P.size - 1, i)), Q);
        }
    }

    Matrix<int> r_hashes(M.size - P.size + 1);
    for (int i = 0; i < r_hashes.size; ++i) {
        for (int j = 0; j < P.size; ++j) {
            r_hashes(i, 0) = mod(r_hashes(i, 0) * D<T>() + for_hash(c_hashes(i, j)), Q);
        }
        if (r_hashes(i, 0) == p_hash)
            if (matrix_match(M, i, 0, P)) res++;
        for (int j = 1; j < (c_hashes.size - P.size + 1); ++j) {
            r_hashes(i, j) = mod(D<T>() * (r_hashes(i, j - 1) - for_hash(c_hashes(i, j - 1)) * h) +
                              for_hash(c_hashes(i, j + P.size - 1)), Q);

            if (r_hashes(i, j) == p_hash)
                if (matrix_match(M, i, j, P)) res++;
        }
    }


    return res;
}