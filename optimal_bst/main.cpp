#include "bst.hpp"
#include "optimal_bst.hpp"

#include <iostream>

int main() {
    std::cout << "Hello, World!" << std::endl;
    int nums[] = {1, 2, 3, 4, 5};
    std::vector<double> p = {0.15, 0.10, 0.05, 0.10, 0.20};
    std::vector<double> q = {0.05, 0.10, 0.05, 0.05, 0.05, 0.10};


    auto rootMatrix = optimalBSTRootMatrix(p, q);
    for (int i = 1; i <= 5; i++) {
        for (int j = 1; j <= 5; j++) {
            std::cout << rootMatrix[i][j] + 1 << "   ";
        }
        std::cout << std::endl;
    }
    return 0;
}
