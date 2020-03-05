#include "binomial_heap.hpp"

BinomialHeap::BinomialHeap() :
        _head(nullptr) {}

BinomialHeap::BinomialHeap(BinomialNode *head) {
    _head = head;
}

void BinomialHeap::printStep(BinomialNode *node, int level) {
    if (node == nullptr) return;

    std::cout << '|';
    for (int i = 0; i < level; i++) {
        std::cout << '\t' << '|';
    }
    std::cout << *(node->data()) << std::endl;
    printStep(node->child, level + 1);
    printStep(node->sibling, level);
}

void BinomialHeap::print() {
    printStep(_head, 0);
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

void insertNode(BinomialHeap &heap, BinomialNode *node) {
    auto newHeap = new BinomialHeap(node);
    heap = binomialHeapUnion(*newHeap, heap);
}

BinomialNode *binomialHeapMerge(BinomialHeap heapL, BinomialHeap heapR) {
    BinomialNode *newHead = nullptr, *newPtr = nullptr;
    BinomialNode *ptr1 = heapL.head();
    BinomialNode *ptr2 = heapR.head();

    while (ptr1 || ptr2) {
        if (ptr1 && ptr2) {
            if (ptr1->degree() < ptr2->degree()) {
                if (newHead) {
                    newPtr->sibling = ptr1;
                    newPtr = newPtr->sibling;
                } else {
                    newPtr = newHead = ptr1;
                }
                ptr1 = ptr1->sibling;
            } else {
                if (newHead) {
                    newPtr->sibling = ptr2;
                    newPtr = newPtr->sibling;
                } else {
                    newPtr = newHead = ptr2;
                }
                ptr2 = ptr2->sibling;
            }
        } else if (ptr1) {
            if (newHead) {
                newPtr->sibling = ptr1;
                newPtr = newPtr->sibling;
            } else {
                newPtr = newHead = ptr1;
            }
            ptr1 = ptr1->sibling;
        } else {
            if (newHead) {
                newPtr->sibling = ptr2;
                newPtr = newPtr->sibling;
            } else {
                newPtr = newHead = ptr2;
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

BinomialHeap binomialHeapUnion(BinomialHeap heapL, BinomialHeap heapR) {
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

