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
    std::cout << std::endl;

    auto tmp = *heap.head()->sibling->child->sibling->data();
    tmp.decAveragePoint(50);
    decreaseKey(heap, heap.head()->sibling->child->sibling, &tmp);

    heap.print();
    std::cout << std::endl;

    deleteNode(heap, heap.head()->sibling->child->sibling);
    heap.print();
    std::cout << std::endl;



    return 0;
}
