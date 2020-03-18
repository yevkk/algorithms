#include "bst.hpp"
#include "optimal_bst.hpp"

#include <iostream>

void example1() {
    std::vector<double> p = {15, 10, 5, 10, 20};
    std::vector<double> q = {5, 10, 5, 5, 5, 10};
    std::vector<int> data = {1, 2, 3, 4, 5};

    optimalBST(data, p, q).print();
}

int main() {
    example1();

    return 0;
}
