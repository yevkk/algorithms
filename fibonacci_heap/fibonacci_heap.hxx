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
        _trees_count{0},
        _min{nullptr} {}


template<typename DataType>
template<typename OStream>
void
FibonacciHeap<DataType>::_printStep(OStream &output, FibonacciHeap::NodePtr node, unsigned level_size, unsigned level) {
    for (int i = 1; i <= level_size; i++) {
        output << '|';
        for (int j = 0; j < level; j++) {
            output << '\t' << '|';
        }
        if (!node.get()) {
            output << "*\n";
        } else {
            output << node->data << " (degree: " << node->degree << ")\n";
            _printStep(output, node->child, node->degree, level + 1);
        }

        node = node->right;
    }
}

template<typename DataType>
template<typename OStream>
void FibonacciHeap<DataType>::print(OStream &output) {
    if (_n == 0) {
        output << "|*\n";
    } else _printStep(output, _min, _trees_count, 0);
}

template<typename DataType>
void FibonacciHeap<DataType>::insert(const DataType &key) {
    NodePtr new_node = std::make_shared<FBNode<DataType>>(key);

    if (_min.get()) {
        _min->left->right = new_node;
        new_node->left = _min->left;

        _min->left = new_node;
        new_node->right = _min;

        if (key < _min->data) _min = new_node;
    } else {
        _min = new_node;
        new_node->left = new_node;
        new_node->right = new_node;
    }
    _n++;
    _trees_count++;
}

template<typename DataType>
DataType FibonacciHeap<DataType>::min() {
    return (_min.get()) ? _min.data : DataType();
}

template<typename T>
FibonacciHeap<T> heapUnion(FibonacciHeap<T>* heapL, FibonacciHeap<T>* heapR) {
    if (!heapL->_min.get()){
        delete heapL;
        return *heapR;
    }

    if (!heapR->_min.get()){
        delete heapR;
        return *heapL;
    }

    auto tailL = heapL->_min->left;
    auto tailR = heapR->_min->left;

    tailR->right = heapL->_min;
    heapL->_min->left = tailR;
    tailL->right = heapR->_min;
    heapR->_min->left = tailL;

    FibonacciHeap<T> result;
    result._min = (heapL->_min->data < heapR->_min->data) ? heapL->_min : heapR->_min;
    result._n = heapL->_n + heapR->_n;
    result._trees_count = heapL->_trees_count + heapR->_trees_count;

    delete heapL;
    delete heapR;

    return result;
}


#endif //FIBONACCI_HEAP_FIBONACCI_HEAP_HXX
