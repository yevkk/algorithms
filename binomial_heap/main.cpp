#include "department.hpp"
#include "binomial_heap.hpp"
#include <iostream>

inline bool operator<(std::pair<int, int> &pairL, std::pair<int, int> &pairR) {
    return pairL.second < pairR.second;
}

inline bool operator>(std::pair<int, int> &pairL, std::pair<int, int> &pairR) {
    return !(pairL < pairR);
}

inline bool operator==(std::pair<int, int> &pairL, std::pair<int, int> &pairR) {
    return (!(pairL < pairR)) && (!(pairL > pairR));
}

inline bool operator>=(std::pair<int, int> &pairL, std::pair<int, int> &pairR) {
    return !(pairL < pairR);
}

inline bool operator<=(std::pair<int, int> &pairL, std::pair<int, int> &pairR) {
    return !(pairL > pairR);
}

inline std::ostream &operator<<(std::ostream &os, std::pair<int, int> &pair) {
    os << pair.first << ",  " << pair.second;
    return os;
}

void example1() {
    auto students = getStudentsFromDB("../../department.db");
    BinomialHeap<Student> heap(nullptr);
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
}

void example2() {
    auto students = getStudentsFromDB("../../department.db");
    BinomialHeap<Student> heap1(nullptr);
    for (int i = 0; i < 50; i++) {
        insertNode(heap1, new BinomialNode<Student>(students[i]));
    }
    heap1.print();
    std::cout << std::endl;
};

void example3(int count) {
    BinomialHeap<std::pair<int, int>> heapOfPairs;
    for (int i = 0; i < count; i++) {
        insertNode(heapOfPairs, new BinomialNode<std::pair<int, int>>(new std::pair<int, int>(5, i)));
    }

    heapOfPairs.print();
    std::cout << std::endl;

    for (int i = 0; i < count; i++) {
        std::cout << *(extractMin(heapOfPairs)->data()) << std::endl;
    }
}

int main() {
    example3(20);

    return 0;
}


