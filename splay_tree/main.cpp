#include "department.hpp"
#include "splay_tree.hpp"
#include <iostream>
#include <random>
#include <ctime>

int rand_int(int min, int max) {
    static std::random_device rd;
    static std::seed_seq seed{rd(), static_cast<unsigned int>(time(nullptr))};
    static std::mt19937_64 gen(seed);
    std::uniform_int_distribution<int> dist(min, max);

    return dist(gen);
}

void example1(int count = 10) {
    auto students = getStudentsFromDB("../../department.db");
    SplayTree<Student> tree;

    for (int i = 0; i < count; i++) {
        tree.insert(*(students[i]));
        tree.print();
        std::cout << std::endl << std::endl;
    }
}

void example2(int count = 10) {
    int* num = new int(count);
    SplayTree<int> tree;

    for (int i = 0; i < count; i++) {
        num[i] = rand_int(0, 50);
        tree.insert(num[i]);
        tree.print();
        std::cout << std::endl << std::endl;
    }

    int index = 5;
    std::cout << "Searching for " << num[index] << std::endl;
    std::cout << "Result: " << std::boolalpha << tree.contains(num[index]) << std::endl;
    tree.print();
    std::cout << std::endl << std::endl;

    index = 3;
    std::cout << "Deleting " << num[index] << std::endl;
    tree.remove(num[index]);
    tree.print();
}

int main() {
    example2(11);
    return 0;
}
