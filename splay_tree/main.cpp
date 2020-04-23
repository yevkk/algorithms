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

//creating splay tree with Student elements;
void example1(int count = 10) {
    if (count > 50) count = 50;
    if (count < 0) count = 0;

    auto students = getStudentsFromDB("../../department.db");
    SplayTree<Student> tree;

    //std::cout << std::boolalpha << (*(students[1]) == *(students[1])) << std::endl;

    for (int i = 0; i < count; i++) {
        tree.insert(*(students[i]));
        tree.print();
        std::cout << std::endl << std::endl;
    }
}

//creating splay tree with Student elements;
//searching for element;
//removing an element;
void example2(int count = 10) {
    auto students = getStudentsFromDB("../../department.db");
    SplayTree<Student> tree;

    for (int i = 0; i < count; i++) {
        tree.insert(*(students[i]));
    }

    tree.print();
    std::cout << std::endl << std::endl;

    int index = 5;
    std::cout << "Searching for " << *(students[index]) << std::endl;
    std::cout << "Result: " << std::boolalpha << tree.contains(*(students[index])) << std::endl;
    tree.print();
    std::cout << std::endl << std::endl;

    index = 1;
    std::cout << "Deleting " << *(students[index]) << std::endl;
    tree.remove(*(students[index]));
    tree.print();
    std::cout << std::endl << std::endl;

    index = 3;
    std::cout << "Deleting " << *(students[index]) << std::endl;
    tree.remove(*(students[index]));
    tree.print();
    std::cout << std::endl << std::endl;

    index = 4;
    std::cout << "Deleting " << *(students[index]) << std::endl;
    tree.remove(*(students[index]));
    tree.print();
    std::cout << std::endl << std::endl;

}

//join trees
//using int data for simplifying division of data on sets >x and <=x
void example3(int count = 10) {
    int *nums1 = new int[count];
    int *nums2 = new int[count];
    SplayTree<int> tree1;
    SplayTree<int> tree2;

    for (int i = 0; i < count; i++) {
        nums1[i] = rand_int(0, 50);
        tree1.insert(nums1[i]);
    }
    std::cout << "Tree 1 (< 50):\n";
    tree1.print();
    std::cout << std::endl << std::endl;

    for (int i = 0; i < count; i++) {
        nums2[i] = rand_int(50, 100);
        tree2.insert(nums2[i]);
    }
    std::cout << "Tree 2 (> 50):\n";
    tree2.print();
    std::cout << std::endl << std::endl;

    std::cout << "Join result:\n";
    tree2.join(tree1);
    tree2.print();
    std::cout << std::endl << std::endl;
}

//split tree
void example4(int count = 10) {
    if (count > 50) count = 50;

    auto num = new int[count];
    SplayTree<int> tree1;

    for (int i = 0; i < count; i++) {
        num[i] = rand_int(0, 50);
        tree1.insert(num[i]);
    }
    std::cout << "Initial tree:\n";
    tree1.print();
    std::cout << std::endl << std::endl;

    auto tree2 = tree1.split(num[5]);
    std::cout << "Tree (>" << num[5] << "):\n";
    tree2.print();
    std::cout << std::endl << std::endl;

    std::cout << "Tree (<=" << num[5] << "):\n";
    tree1.print();
    std::cout << std::endl << std::endl;

}


int main() {
    example1 (10);

    return 0;
}
