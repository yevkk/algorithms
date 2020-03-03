#include "department.hpp"
#include "rb_tree.hpp"

#include <iostream>

int main() {
    auto students = getStudentsFromDB("../../department.db");
    auto tree = new RBTree();
    for (auto &e:students) {
        auto node = new RBNode(e);
        tree->insertNode(node);
    }

    tree->print();
    std::cout << std::endl << std::endl;

    for (int i = 1; i <= 50; i++) {
        std::cout << *(tree->osSelect(i)->data()) << std::endl;
    }
    std::cout << std::endl << std::endl;

    for (int i = 1; i <= 40; i++) {
        tree->deleteNode(tree->root());
    }

    tree->print();
    std::cout << std::endl << std::endl;


    return 0;
}
