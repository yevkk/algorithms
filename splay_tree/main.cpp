#include "department.hpp"
#include "splay_tree.hpp"
#include <iostream>

void example1() {
    auto students = getStudentsFromDB("../../department.db");
    SplayTree<Student> tree;

    for (int i = 0; i < 5; i++) {
        tree.insert(*(students[i]));
        tree.print();
        std::cout << std::endl << std::endl;
    }
}

int main() {
    example1();
    return 0;
}
