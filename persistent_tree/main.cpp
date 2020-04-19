#include <iostream>

#include "persistent_tree.hpp"

int main() {
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


    return 0;
}
