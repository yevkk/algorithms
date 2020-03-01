#include "department.hpp"
#include "rb_tree.hpp"

#include <iostream>

int main() {
    auto students = getStudentsFromDB("../../department.db");
    auto tree = new RBTree();
    for (auto &e:students) {
        auto node = new RBNode(e);
//        tree->insert(node);
    }
    //tree->print();
    return 0;
}
