#ifndef BINOMIAL_HEAP_BINOMIAL_HEAP_HPP
#define BINOMIAL_HEAP_BINOMIAL_HEAP_HPP


#include "binominal_node.hpp"

class BinomialHeap {
private:
    BinomialNode *_head;
public:
    BinomialHeap();

    explicit BinomialHeap(BinomialNode *head);

    BinomialNode *head();

    void setHead(BinomialNode *node);

    BinomialNode *min();

};

BinomialHeap insertNode(BinomialHeap heap, BinomialNode node);

BinomialNode *binomialHeapMerge(BinomialHeap heapL, BinomialHeap heapR);

void binomialLink(BinomialNode *resRoot, BinomialNode *resChild);

BinomialHeap binominalHeapUnion(BinomialHeap heapL, BinomialHeap heapR);




#endif //BINOMIAL_HEAP_BINOMIAL_HEAP_HPP
