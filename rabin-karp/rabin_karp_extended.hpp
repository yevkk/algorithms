#pragma once
#include "matrix.hpp"

int hash(char c) {
    return c;
}

template <typename T>
int rabin_karp_extended(Matrix<T> M, Matrix<T> P) {
    int res = 0;
    if (P.size > M.size) return 0;

    M.print(); //TODO: delete;
    std::cout << std::endl;

    int p_hash = 0;
    for (int i = 0; i < P.size; ++i)
        for (int j = 0; j < P.size; ++j)
            p_hash += hash(P(i, j));

    Matrix<int> c_hashes(M.size);
    for (int i = 0; i < c_hashes.size; ++i) {
        for (int j = 0; j < P.size; ++j) {
            c_hashes(0, i) += hash(M(j, i));
        }
        for (int j = 1; j < (c_hashes.size - P.size + 1); ++j) {
            c_hashes(j, i) = c_hashes(j - 1, i) - hash(M(j - 1, i)) + hash(M(j + P.size - 1, i));
        }
    }

    c_hashes.print(); //TODO: delete;
    std::cout << std::endl;

    Matrix<int> r_hashes(M.size - P.size + 1);
    for (int i = 0; i < r_hashes.size; ++i){
        for (int j = 0; j < P.size; ++j) {
            r_hashes(i, 0) += hash(c_hashes(i, j));
        }

        for (int j = 1; j < (c_hashes.size - P.size + 1); ++j) {
            r_hashes(i, j) = r_hashes(i, j - 1) - hash(c_hashes(i, j - 1)) + hash(c_hashes(i, j + P.size - 1));
        }
    }

    r_hashes.print(); //TODO: delete;
    std::cout << std::endl;


    return res;
}