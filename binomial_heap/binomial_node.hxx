#ifndef BINOMIAL_HEAP_BINOMIAL_NODE_HXX
#define BINOMIAL_HEAP_BINOMIAL_NODE_HXX

#include "binomial_node.hpp"

template<typename DataType>
BinomialNode<DataType>::BinomialNode(DataType *data) :
        _data(data),
        parent(nullptr),
        sibling(nullptr),
        child(nullptr),
        _degree(0) {}

template<typename DataType>
DataType *BinomialNode<DataType>::data() {
    return _data;
}

template<typename DataType>
int BinomialNode<DataType>::degree() {
    return _degree;
}

template<typename DataType>
void BinomialNode<DataType>::incDegree() {
    _degree++;
}

template<typename DataType>
void BinomialNode<DataType>::setData(DataType *data, bool deletePrev) {
    if (deletePrev)
        delete _data;
    _data = data;
}

#endif //BINOMIAL_HEAP_BINOMIAL_NODE_HXX
