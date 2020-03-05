#include "department.hpp"
#include "binomial_heap.hpp"
#include <iostream>

int main() {
    auto students = getStudentsFromDB("../../department.db");
    BinomialHeap heap;
    for (int i = 0; i < 10; i++) {
        insertNode(heap, new BinomialNode(students[i]));
        heap.print();
    }
    heap.print();
    return 0;
}
