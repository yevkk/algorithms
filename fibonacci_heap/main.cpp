#include "fibonacci_heap.hpp"

#include <iostream>
#include <utility>

int main() {
    FibonacciHeap<int> heap;
    heap.insert(3);
    heap.insert(5);
    heap.insert(2);
    heap.insert(7);
    heap.insert(1);
    heap.insert(4);

    heap.print(std::cout);
    std::cout << std::endl << std::endl;

    heap.extractMin();
    heap.print(std::cout);
    std::cout << std::endl << std::endl;

    heap.deleteNode(heap.minNode()->child);
    heap.print(std::cout);
    std::cout << std::endl << std::endl;


    return 0;
}
