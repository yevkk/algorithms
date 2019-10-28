#include "rabin_karp_extended.hpp"
#include <iostream>
#include <vector>

int main() {
    std::vector<std::vector<int>> a = {{1, 1, 1, 1},
                                       {2, 2, 2, 2},
                                       {3, 3, 3, 3},
                                       {4, 4, 4, 4}};
    Matrix<int> M(4);
    Matrix<int> P(2);
    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++)
            M(i, j) = a[i][j];

    rabin_karp_extended<int>(M, P);

    return 0;
}