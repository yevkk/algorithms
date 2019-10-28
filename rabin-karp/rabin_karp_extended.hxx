#pragma once
#include "rabin_karp_extended.hpp"

int hash(char c) {
    return c;
}

template <typename T>
int rabin_karp_extended(Matrix<T> M, Matrix<T> P) {
    int res = 0;
    if (P.size > M.size) return 0;

    M.print(); //TODO: delete;

    int p_hash = 0;
    for (int i = 0; i < P.size; ++i)
        for (int j = 0; j < P.size; ++j)
            p_hash += hash(P(i, j));

    Matrix<int> hashes(M.size);
    for (int i = 0; i < M.size; ++i) {
        for (int j = 0; j < P.size; ++j) {
            hashes(0, i) += hash(M(j, i));
        }
        for (int j = 1; j < (M.size - P.size + 1); ++j) {
            hashes(j, i) = hashes(j - 1, i) - hash(M(j - 1, i)) + hash(M(j + P.size - 1, i));
        }
    }

    hashes.print(); //TODO: delete;

    return res;
}