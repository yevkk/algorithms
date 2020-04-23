#include "bplus_tree.hpp"
#include "../random.h"
#include "department.hpp"
#include <iostream>
#include <algorithm>

void exampleInt() {
    int size = 20;
    std::vector<int> data(size);

    for (int i = 0; i < size; i++){
        data[i] = i + 1;
    }

    std::random_device rd;
    std::mt19937 g(rd());
    std::shuffle(data.begin(), data.end(), g);

    BPlusTree<int> tree(3);

    for(auto &item: data) {
        tree.insert(item);
    }

    tree.print(std::cout);
    std::cout << std::endl << std::endl;
    tree.printSorted(std::cout);
    std::cout << std::endl << std::endl;

    std::shuffle(data.begin(), data.end(), g);

    for(auto &item: data) {
        std::cout << "DELETE " << item << "\n";
        tree.remove(item);
        tree.print(std::cout);
        std::cout << std::endl << std::endl;
    }
}

void exampleStudents() {
    auto students = getStudentsFromDB("../../department.db");
    BPlusTree<Student> tree(3);
    for (auto &item:students) {
        tree.insert(*item);
    }
    tree.print(std::cout);
    std::cout << std::endl << std::endl;
    tree.printSorted(std::cout);
    std::cout << std::endl << std::endl;

    std::random_device rd;
    std::mt19937 g(rd());
    std::shuffle(students.begin(), students.end(), g);

    for (int i = 0; i < 50; i++) {
        std::cout << "DELETE " << *students[i] << "\n";
        tree.remove(*students[i]);
    }

    std::cout << std::endl << std::endl;
    tree.print(std::cout);

    for (int i = 0; i < 15; i++) {
        tree.insert(*students[i]);
    }

    std::cout << std::endl << std::endl;
    tree.print(std::cout);
}

int main() {
    exampleStudents();

    return 0;
}
