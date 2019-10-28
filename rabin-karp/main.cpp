#include "rabin_karp_extended.hpp"
#include <iostream>
#include <vector>

int main() {
    std::vector<std::vector<char>> a = {{'a', 'f', 'g', 'd'},
                                       {'v', 'a', 'f', 'o'},
                                       {'g', 'v', 'a', 'a'},
                                       {'a', 'f', 'g', 'b'}};

    std::vector<std::vector<char>> b = {{'a', 'f'},
                                       {'v', 'a'}};
    Matrix<char> M(4);
    Matrix<char> P(2);
    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++)
            M(i, j) = a[i][j];

    for (int i = 0; i < 2; i++)
        for (int j = 0; j < 2; j++)
            P(i, j) = b[i][j];

    std::cout << std::endl << rabin_karp_extended<char>(M, P);

    return 0;
}