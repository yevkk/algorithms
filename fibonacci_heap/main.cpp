#include "fibonacci_heap.hpp"

#include <iostream>

int main() {
    FibonacciHeap<int> heap1;
    FibonacciHeap<int> heap2;
    heap1.insert(3);
    heap1.insert(5);
    heap1.insert(2);
    heap1.print(std::cout);
    std::cout << std::endl << std::endl;

    heap2.insert(7);
    heap2.insert(1);
    heap2.insert(4);
    heap2.print(std::cout);
    std::cout << std::endl << std::endl;

    auto heap3 = heapUnion(&heap1, &heap2);
    heap3.print(std::cout);

    return 0;
}
