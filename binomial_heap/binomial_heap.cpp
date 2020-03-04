#include "binomial_heap.hpp"

BinomialHeap::BinomialHeap() :
        _head(nullptr) {}

BinomialHeap::BinomialHeap(BinomialNode *head) {
    _head = head;
}

BinomialNode *BinomialHeap::head() {
    return _head;
}