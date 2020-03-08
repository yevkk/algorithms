#include "binomial_heap.hpp"

BinomialHeap::BinomialHeap() :
        _head(nullptr) {}

BinomialHeap::BinomialHeap(BinomialNode *head) {
    _head = head;
}

BinomialHeap::~BinomialHeap() = default;

void BinomialHeap::printStep(BinomialNode *node, int level) {
    if (node == nullptr) return;

    std::cout << '|';
    for (int i = 0; i < level; i++) {
        std::cout << '\t' << '|';
    }
    std::cout << *(node->data()) << " (degree: " << node->degree() << ")" << std::endl;
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

BinomialHeap binomialHeapUnion(BinomialHeap &heapL, BinomialHeap &heapR) {
    static int a = 0;
    a++;

    auto res = new BinomialHeap(binomialHeapMerge(heapL, heapR));
    delete &heapL;
    delete &heapR;

    if (!res->head()) {
        return *res;
    }

    BinomialNode *prevX = nullptr;
    BinomialNode *x = res->head();
    BinomialNode *nextX = x->sibling;

    while (nextX) {
        std::cout << a;
        if ((x->degree() != nextX->degree()) || (nextX->sibling && nextX->sibling->degree() == x->degree())) {
            prevX = x;
            x = nextX;
        } else {
            if (*(x->data()) <= *(nextX->data())) {
                x->sibling = nextX->sibling;
                binomialLink(x, nextX);
            } else {
                if (!prevX) {
                    res->setHead(nextX);
                } else {
                    prevX->sibling = nextX;
                }
                binomialLink(nextX, x);
                x = nextX;
            }
        }
        nextX = x->sibling;
    }

    return *res;
}

