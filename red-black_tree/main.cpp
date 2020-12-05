#include "department.hpp"
#include "rb_tree.hpp"

#include <iostream>

int main() {
    std::vector<int> a{3, 2, 1, 6, 34, 21, 65, 76, 4, 11, 32, 78, 44, 33};
    RBTree A;
    for (const auto& item : a) {
        A.insertNode(new RBNode(item));
    }
    A.print();
    std::cout << "\n\n\n";
    std::vector<int> b{33, 76, 21, 34, 2, 1, 3, 44, 6, 11, 4};
    for (const auto& item : b) {
        A.deleteNode(A.search(A.root(), item));
        std::cout << "DELETED " << item << std::endl;
        A.print();
        std::cout << "\n\n\n";
    }

    return 0;
}
