#include "persistent_tree.hpp"
#include "department.hpp"

#include <iostream>

void example1() {
    PersistentTree<int> tree;
    int a[] = {1, 2, 3, 4, 5, 6};
    tree.insert(a + 1);
    tree.insert(a + 3);
    tree.insert(a + 2);
    tree.insert(a + 0);
    tree.insert(a + 4);

    tree.deleteNode(a + 1);
    tree.insert(a + 5);
    tree.deleteNode(a + 4);
    std::cout << std::endl << std::endl;
    tree.printAll(std::cout);
    std::cout << std::endl << std::endl;
    tree.printChangeLog(std::cout);
}

void example2() {
    auto students = getStudentsFromDB("../../department.db");
    PersistentTree<Student> tree;

    for (auto &item:students) {
        tree.insert(item);
    }
    tree.deleteNode(students[36]);
    tree.deleteNode(students[43]);
    tree.deleteNode(students[12]);
    tree.deleteNode(students[21]);
    tree.deleteNode(students[7]);

    tree.clear();
    tree.insert(students[4]);

    tree.printAll(std::cout);
    std::cout << std::endl << std::endl;
    tree.printChangeLog(std::cout, true);
}

int main() {

    example1();
    return 0;
}
