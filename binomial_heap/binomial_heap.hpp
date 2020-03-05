#ifndef BINOMIAL_HEAP_BINOMIAL_HEAP_HPP
#define BINOMIAL_HEAP_BINOMIAL_HEAP_HPP


#include "binominal_node.hpp"

class BinomialHeap {
private:
    BinomialNode *_head;



public:
    void printStep(BinomialNode *node, int level);

    BinomialHeap();

    void print();

    explicit BinomialHeap(BinomialNode *head);

    BinomialNode *head();

    void setHead(BinomialNode *node);

    BinomialNode *min();

};

void insertNode(BinomialHeap &heap, BinomialNode *node);

BinomialNode *binomialHeapMerge(BinomialHeap heapL, BinomialHeap heapR);

void binomialLink(BinomialNode *resRoot, BinomialNode *resChild);

BinomialHeap binomialHeapUnion(BinomialHeap heapL, BinomialHeap heapR);


#endif //BINOMIAL_HEAP_BINOMIAL_HEAP_HPP
