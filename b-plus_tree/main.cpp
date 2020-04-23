#include "bplus_tree.hpp"
#include "../random.h"
#include "department.hpp"
#include <iostream>
#include <algorithm>

void example1() {
    BPlusTree<int> tree(3);
    for (int i = 0; i < 30; i++) {
        int number = Random::randomInt(0, 1000);
        tree.insert(i);
    }

    std::cout << std::endl << std::endl;
    tree.print(std::cout);
    std::cout << std::endl << std::endl;
    tree.printSorted(std::cout);
    std::cout << std::endl << std::endl;
    std::cout << std::boolalpha << tree.includes(3);
}

void example2() {
    int size = 30;
    BPlusTree<int> tree(3);
    std::vector<int> data(size, 0);
    for (int i = 0; i < size; i++){
        data[i] =  Random::randomInt(0, 500);
    }

    for (auto &item: data) {
        tree.insert(item);
    }

    tree.print(std::cout);
    std::cout << "\n\n";

    std::random_device rd;
    std::mt19937 g(rd());
    std::shuffle(data.begin(), data.end(), g);

    for (auto &item:data) {
        std::cout << "DELETING " << item << "\n";
        tree.remove(item);
        tree.print(std::cout);
        std::cout << "\n\n";
    }
}

void exampleStudents() {
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
