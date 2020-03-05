#include "binomial_heap.hpp"

BinomialHeap::BinomialHeap() :
        _head(nullptr) {}

BinomialHeap::BinomialHeap(BinomialNode *head) {
    _head = head;
}

BinomialNode *BinomialHeap::head() {
    return _head;
}

void BinomialHeap::setHead(BinomialNode *node) {
    _head = node;
}

BinomialNode *BinomialHeap::min() {
    if (_head != nullptr) {
        BinomialNode *min = _head;
        BinomialNode *ptr = _head;

        while (ptr != nullptr) {
            if (*(ptr->data()) < *(min->data())) {
                min = ptr;
                ptr = ptr->sibling;
            }
        }
        return min;
    } else {
        return nullptr;
    }
}

BinomialHeap insertNode(BinomialHeap heap, BinomialNode *node) {
    auto newHeap = new BinomialHeap(node);
    heap = binominalHeapUnion(*newHeap, heap);
}

BinomialNode *binomialHeapMerge(BinomialHeap heapL, BinomialHeap heapR) {
    BinomialNode *newHead = nullptr;
    BinomialNode *ptr1 = heapL.head();
    BinomialNode *ptr2 = heapR.head();

    while (ptr1 || ptr2) {
        if (ptr1 && ptr2) {
            if (ptr1->degree() < ptr2->degree()) {
                if (newHead) {
                    newHead->sibling = ptr1;
                    newHead = newHead->sibling;
                } else {
                    newHead = ptr1;
                }
                ptr1 = ptr1->sibling;
            } else {
                if (newHead) {
                    newHead->sibling = ptr2;
                    newHead = newHead->sibling;
                } else {
                    newHead = ptr2;
                }
                ptr2 = ptr2->sibling;
            }
        } else if (ptr1) {
            if (newHead) {
                newHead->sibling = ptr1;
                newHead = newHead->sibling;
            } else {
                newHead = ptr1;
            }
            ptr1 = ptr1->sibling;
        } else {
            if (newHead) {
                newHead->sibling = ptr2;
                newHead = newHead->sibling;
            } else {
                newHead = ptr2;
            }
            ptr2 = ptr2->sibling;
        }
    }
    return newHead;
}

void binomialLink(BinomialNode *resRoot, BinomialNode *resChild) {
    resChild->parent = resRoot;
    resChild->sibling = resRoot->child;
    resRoot->child = resChild;
    resRoot->incDegree();
}

BinomialHeap binominalHeapUnion(BinomialHeap heapL, BinomialHeap heapR) {
    auto res = new BinomialHeap(binomialHeapMerge(heapL, heapR));
    delete &heapL;
    delete &heapR;

    if (res->head() == nullptr) {
        return *res;
    }

    BinomialNode *prev_x = nullptr;
    BinomialNode *x = res->head();
    BinomialNode *next_x = x->sibling;

    while (next_x) {
        if ((x->degree() != next_x->degree()) ||
            (next_x->sibling != nullptr && next_x->sibling->degree() && next_x->sibling->degree() == x->degree())) {
            prev_x = x;
            x = next_x;
        } else {
            if (*(x->data()) <= *(next_x->data())) {
                x->sibling = next_x->sibling;
                binomialLink(x, next_x);
            } else {
                if (!prev_x) {
                    res->setHead(next_x);
                } else {
                    prev_x->sibling = next_x;
                    binomialLink(next_x, x);
                    x = next_x;
                }
            }
        }
        next_x = x->sibling;
    }
    return *res;
}

