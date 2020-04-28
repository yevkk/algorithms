#ifndef FIBONACCI_HEAP_FIBONACCI_HEAP_HXX
#define FIBONACCI_HEAP_FIBONACCI_HEAP_HXX

#include "fibonacci_heap.hpp"

template<typename DataType>
FBNode<DataType>::FBNode(const DataType &data) :
        data{data},
        parent{nullptr},
        child{nullptr},
        left{nullptr},
        right{nullptr},
        degree{0},
        mark{false} {}

template<typename DataType>
FibonacciHeap<DataType>::FibonacciHeap() :
        _n{0},
        _min{nullptr} {}


#endif //FIBONACCI_HEAP_FIBONACCI_HEAP_HXX
