#ifndef BINOMIAL_HEAP_BINOMIAL_HEAP_HXX
#define BINOMIAL_HEAP_BINOMIAL_HEAP_HXX

#include "binomial_heap.hpp"
#include "infnull.hpp"

template<typename DataType>
BinomialHeap<DataType>::BinomialHeap() :
        _head(nullptr) {}

template<typename DataType>
BinomialHeap<DataType>::BinomialHeap(BinomialNode<DataType> *head) {
    _head = head;
}

template<typename DataType>
BinomialHeap<DataType>::~BinomialHeap() = default;

template<typename DataType>
void BinomialHeap<DataType>::printStep(BinomialNode<DataType> *node, int level) {

    std::cout << '|';
    for (int i = 0; i < level; i++) {
        std::cout << '\t' << '|';
    }
    if (!node) {
        std::cout << '*' << std::endl;
    } else {
        std::cout << *(node->data()) << " (degree: " << node->degree() << ")" << std::endl;
        printStep(node->child, level + 1);
        printStep(node->sibling, level);
    }
}

template<typename DataType>
void BinomialHeap<DataType>::print() {
    printStep(_head, 0);
}

template<typename DataType>
BinomialNode<DataType> *BinomialHeap<DataType>::head() {
    return _head;
}

template<typename DataType>
void BinomialHeap<DataType>::setHead(BinomialNode<DataType> *node) {
    _head = node;
}

template<typename DataType>
BinomialNode<DataType> *BinomialHeap<DataType>::min() {
    if (_head) {
        BinomialNode<DataType> *min = _head;
        BinomialNode<DataType> *ptr = _head;

        while (ptr) {
            if (*(ptr->data()) < *(min->data())) {
                min = ptr;
            }
            ptr = ptr->sibling;
        }
        return min;
    } else {
        return nullptr;
    }
}


template<typename DataType>
void insertNode(BinomialHeap<DataType> &heap, BinomialNode<DataType> *node) {
    auto newHeap = new BinomialHeap<DataType>(node);
    heap = binomialHeapUnion(*newHeap, heap);
}

template<typename DataType>
void deleteNode(BinomialHeap<DataType> &heap, BinomialNode<DataType> *node) {
    decreaseKey(heap, node, &(null<DataType>::value));
    extractMin(heap);
}

template<typename DataType>
BinomialNode<DataType> *binomialHeapMerge(BinomialHeap<DataType> heapL, BinomialHeap<DataType> heapR) {
    BinomialNode<DataType> *newHead = nullptr, *newPtr = nullptr;
    BinomialNode<DataType> *ptr1 = heapL.head();
    BinomialNode<DataType> *ptr2 = heapR.head();

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

template<typename DataType>
void binomialLink(BinomialNode<DataType> *resRoot, BinomialNode<DataType> *resChild) {
    resChild->parent = resRoot;
    resChild->sibling = resRoot->child;
    resRoot->child = resChild;
    resRoot->incDegree();
}

template<typename DataType>
BinomialHeap<DataType> binomialHeapUnion(BinomialHeap<DataType> &heapL, BinomialHeap<DataType> &heapR) {
    auto res = new BinomialHeap<DataType>(binomialHeapMerge(heapL, heapR));
    delete &heapL;
    delete &heapR;

    if (!res->head()) {
        return *res;
    }

    BinomialNode<DataType> *prevX = nullptr;
    BinomialNode<DataType> *x = res->head();
    BinomialNode<DataType> *nextX = x->sibling;

    while (nextX) {
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

template<typename DataType>
BinomialNode<DataType> *extractMin(BinomialHeap<DataType> &heap) {
    ;
    if (heap.head()) {
        BinomialNode<DataType> *min = heap.head();
        BinomialNode<DataType> *prevMin = nullptr;
        BinomialNode<DataType> *x = heap.head();
        BinomialNode<DataType> *prevX = nullptr;


        while (x) {
            if (*(x->data()) < *(min->data())) {
                min = x;
                prevMin = prevX;
            }
            prevX = x;
            x = x->sibling;
        }

        if (prevMin) {
            prevMin->sibling = min->sibling;
        } else {
            heap.setHead(min->sibling);
        }

        prevX = x = min->child;

        BinomialNode<DataType> *newHead = nullptr, *ptr = nullptr;

        while (x) {
            newHead = new BinomialNode<DataType>(x->data());
            newHead->child = x->child;
            while (newHead->degree() != x->degree()) {
                newHead->incDegree();
            }

            newHead->sibling = ptr;
            ptr = newHead;

            x = x->sibling;
            delete prevX;
            prevX = x;
        }

        BinomialHeap<DataType> newHeap(newHead);

        heap = binomialHeapUnion(newHeap, heap);

        return min;
    } else {
        return nullptr;
    }
}

template<typename DataType>
void decreaseKey(BinomialHeap<DataType> &heap, BinomialNode<DataType> *node, DataType *newValue) {
    assert(*newValue < *(node->data()));
    node->setData(newValue);
    auto y = node;
    auto z = y->parent;

    while (z && (*(y->data()) < *(z->data()))) {
        auto tmp = y->data();
        y->setData(z->data(), false);
        z->setData(tmp, false);
        y = z;
        z = y->parent;
    }
}

#endif //BINOMIAL_HEAP_BINOMIAL_HEAP_HXX

