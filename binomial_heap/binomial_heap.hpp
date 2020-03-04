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

};


#endif //BINOMIAL_HEAP_BINOMIAL_HEAP_HPP
