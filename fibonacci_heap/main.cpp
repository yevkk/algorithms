#include "fibonacci_heap.hpp"

#include <iostream>
#include <algorithm>
#include <random>

void exampleInt() {
    FibonacciHeap<int> heap;
    std::vector<int> data {2, 23, 43, 12, 23 ,21, 34, 13, 3};

    for (int i = 1; i <= data.size(); i++) {
        std::cout << "INSERTING " << data[i-1] << std::endl;
        heap.insert(data[i-1]);
        heap.print(std::cout);
        std::cout << std::endl << std::endl;
    }

    std::cout << "EXTRACTING MIN" << std::endl;
    heap.extractMin();
    heap.print(std::cout);
    std::cout << std::endl << std::endl;

    auto min = heap.minNode();
    auto ptr = min->child->right->child;

    std::cout << "DELETING " << ptr->data << std::endl;
    heap.deleteNode(ptr);
    heap.print(std::cout);
    std::cout << std::endl << std::endl;

    auto ptr2 = min->child->right;
    std::cout << "DECREASING " << ptr2->data << " TO -100" << std::endl;
    heap.decreaseKey(ptr2, -100);
    heap.print(std::cout);
    std::cout << std::endl << std::endl;

}

void exampleStudents() {

    auto students = getStudentsFromDB("../../department.db");
    FibonacciHeap<Student> heap;
    for (int i = 1; i <= 50; i++) {
        std::cout << i << " INSERTING " << *students[i-1] << std::endl;
        heap.insert(*students[i-1]);
        heap.print(std::cout);
        std::cout << std::endl << std::endl;

        if (i % 5 == 0) {
            std::cout << i << " EXTRACTING MIN" << std::endl;
            heap.extractMin();
            heap.print(std::cout);
            std::cout << std::endl << std::endl;
        }
    }
}

int main() {
    exampleInt();


    return 0;
}
