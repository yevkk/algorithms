#ifndef BINOMIAL_HEAP_BINOMIAL_HEAP_HPP
#define BINOMIAL_HEAP_BINOMIAL_HEAP_HPP


#include "binomial_node.hpp"

#include <cassert>

template<typename DataType>
class BinomialHeap {
private:
    BinomialNode<DataType> *_head;


public:
    void printStep(BinomialNode<DataType> *node, int level);

    BinomialHeap();

    ~BinomialHeap();

    void print();

    explicit BinomialHeap(BinomialNode<DataType> *head);

    BinomialNode<DataType> *head();

    void setHead(BinomialNode<DataType> *node);

    BinomialNode<DataType> *min();

};

template<typename DataType>
void insertNode(BinomialHeap<DataType> &heap, BinomialNode<DataType> *node);

template<typename DataType>
void deleteNode(BinomialHeap<DataType> &heap, BinomialNode<DataType> *node);

template<typename DataType>
BinomialNode<DataType> *binomialHeapMerge(BinomialHeap<DataType> heapL, BinomialHeap<DataType> heapR);

template<typename DataType>
void binomialLink(BinomialNode<DataType> *resRoot, BinomialNode<DataType> *resChild);

template<typename DataType>
BinomialHeap<DataType> binomialHeapUnion(BinomialHeap<DataType> &heapL, BinomialHeap<DataType> &heapR);

template<typename DataType>
BinomialNode<DataType> *extractMin(BinomialHeap<DataType> &heap);

template<typename DataType>
void decreaseKey(BinomialHeap<DataType> &heap, BinomialNode<DataType> *node, DataType *newValue);

#include "binomial_heap.hxx"

#endif //BINOMIAL_HEAP_BINOMIAL_HEAP_HPP
