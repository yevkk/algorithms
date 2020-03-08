#include "department.hpp"
#include "binomial_heap.hpp"
#include <iostream>

int main() {
    auto students = getStudentsFromDB("../../department.db");
    BinomialHeap<Student> heap;
    for (int i = 0; i < 10; i++) {
        insertNode(heap, new BinomialNode<Student>(students[i]));
    }
    heap.print();
    for (int i = 0; i < 10; i++) {
        std::cout << *(heap.min()->data()) << std::endl;
    }
    return 0;
}
