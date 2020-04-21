#include "bplus_tree.hpp"
#include "../random.h"
#include "department.hpp"
#include <iostream>

void example1() {
    BPlusTree<int> tree;
    for (int i = 0; i < 50; i++) {
        int number = Random::randomInt(0, 1000);
        tree.insert(number);

    }

    std::cout << std::endl << std::endl;
    tree.print(std::cout);
}

void example2() {
    auto students = getStudentsFromDB("../../department.db");
    BPlusTree<Student> tree;
    for (auto &item:students) {
        tree.insert(*item);
    }

    std::cout << std::endl << std::endl;
    tree.printSorted(std::cout);
}

int main() {
    example2();

    return 0;
}
