#include "rabin_karp_extended.hpp"

int hash(char c) {
    return c;
}

int rabin_karp_extended(Matrix<char> M, Matrix<char> P) {
    int res = 0;
    if (P.size > M.size) return 0;

    int p_hash = 0;
    for (int i = 0; i < P.size; ++i)
        for (int j = 0; j < P.size; ++j)
            p_hash += hash(P(i, j));

    Matrix<int> hashes(M.size);
    for (int i = 0; i < M.size; ++i)

        return res;
}