#ifndef FIBONACCI_HEAP_FIBONACCI_HEAP_HXX
#define FIBONACCI_HEAP_FIBONACCI_HEAP_HXX

#include "fibonacci_heap.hpp"
#include "department.hpp"

#include <cmath>
#include <cassert>
#include <vector>
#include <utility>
#include <string>

template<typename DataType>
FBNode<DataType>::FBNode(const DataType &data) :
        data{data},
        parent{nullptr},
        child{nullptr},
        left{nullptr},
        right{nullptr},
        degree{0},
        mark{false} {}

template<typename DataType>
FibonacciHeap<DataType>::FibonacciHeap() :
        _n{0},
        _trees_count{0},
        _min{nullptr} {}


template<typename DataType>
template<typename OStream>
void
FibonacciHeap<DataType>::_printStep(OStream &output, FibonacciHeap::NodePtr node, unsigned level_size, unsigned level) {
    for (int i = 1; i <= level_size; i++) {
        output << '|';
        for (int j = 0; j < level; j++) {
            output << '\t' << '|';
        }
        if (!node) {
            output << "*\n";
        } else {
            output << node->data << " (degree: " << node->degree << ")\n";
            _printStep(output, node->child, node->degree, level + 1);
        }

        node = node->right;
    }
}

template<typename DataType>
template<typename OStream>
void FibonacciHeap<DataType>::print(OStream &output) {
    if (_n == 0) {
        output << "|*\n";
    } else _printStep(output, _min, _trees_count, 0);
}

template<typename DataType>
void FibonacciHeap<DataType>::insert(const DataType &key) {
    NodePtr new_node = std::make_shared<FBNode<DataType>>(key);

    if (_min) {
        _min->left->right = new_node;
        new_node->left = _min->left;

        _min->left = new_node;
        new_node->right = _min;

        if (key < _min->data) _min = new_node;
    } else {
        _min = new_node;
        new_node->left = new_node;
        new_node->right = new_node;
    }
    _n++;
    _trees_count++;
}

template<typename DataType>
DataType FibonacciHeap<DataType>::min() {
    return (_min) ? _min.data : DataType();
}

template<typename DataType>
std::shared_ptr<FBNode<DataType>> FibonacciHeap<DataType>::minNode() {
    return _min;
}


template<typename DataType>
void FibonacciHeap<DataType>::_link(FibonacciHeap::NodePtr res_child, FibonacciHeap::NodePtr res_parent) {
    res_child->left->right = res_child->right;
    res_child->right->left = res_child->left;

    if (res_parent->child) {
        auto last_child = res_parent->child->left;

        last_child->right = res_child;
        res_child->left = last_child;
        res_child->right = res_parent->child;
        res_parent->child->left = res_child;

        res_parent->child = res_child;
    } else {
        res_child->right = res_child->left = res_child;
        res_parent->child = res_child;
    }
    res_parent->degree++;
    res_parent->mark = false;

    res_child->parent = res_parent;
}


template<typename DataType>
void FibonacciHeap<DataType>::_consolidate() {
    std::vector<NodePtr> A(log2(_n) + 1, nullptr);

    auto root = _min;
    for (int i = 1; i <= _trees_count; i++) {
        int d = root->degree;
        while (A[d]) {
            auto ptr = A[d];
            if (root->data > ptr->data) {
                std::swap(root, ptr);
            }
            _link(ptr, root);
            A[d] = nullptr;
            d++;
        }
        A[d] = root;
        root = root->right;
    }

    _min = nullptr;
    for (auto &item:A) {
        if (item) {
            if (!_min) {
                _min = item;
                _min->left = _min->right = _min;
                _trees_count = 1;
            } else {
                auto tail = _min->left;
                tail->right = item;
                item->left = tail;
                item->right = _min;
                _min->left = item;
                _trees_count++;

                if (_min->data > item->data)
                    _min = item;
            }
        }
    }
}

template<typename DataType>
DataType FibonacciHeap<DataType>::extractMin() {
    auto min_node = _min;
    if (!min_node)
        return DataType();

    if (_n == 1) {
        _min = nullptr;
        return min_node->data;
    }

    auto child = min_node->child;
    if (child) {
        for (int i = 1; i <= min_node->degree; i++) {
            child->parent = nullptr;
            child = child->right;
        }

        auto first_child = min_node->child;
        auto last_child = min_node->child->left;
        auto tail = min_node->left;

        first_child->left = tail;
        tail->right = first_child;
        min_node->right->left = last_child;
        last_child->right = min_node->right;
    }

    _n--;
    _trees_count = _trees_count - 1 + min_node->degree;

    _min = _min->right;
    _consolidate();

    return min_node->data;
}


template<typename T>
FibonacciHeap<T> heapUnion(FibonacciHeap<T> *heapL, FibonacciHeap<T> *heapR) {
    if (!heapL->_min) {
        delete heapL;
        return *heapR;
    }

    if (!heapR->_min) {
        delete heapR;
        return *heapL;
    }

    auto tailL = heapL->_min->left;
    auto tailR = heapR->_min->left;

    tailR->right = heapL->_min;
    heapL->_min->left = tailR;
    tailL->right = heapR->_min;
    heapR->_min->left = tailL;

    FibonacciHeap<T> result;
    result._min = (heapL->_min->data < heapR->_min->data) ? heapL->_min : heapR->_min;
    result._n = heapL->_n + heapR->_n;
    result._trees_count = heapL->_trees_count + heapR->_trees_count;

    delete heapL;
    delete heapR;

    return result;
}

template<typename DataType>
void FibonacciHeap<DataType>::_cut(FibonacciHeap::NodePtr x, FibonacciHeap::NodePtr y) {
    x->left->right = x->right;
    x->right->left = x->left;
    if (x == y->child) {
        y->child = x->right;
    }
    y->degree--;

    _min->left->right = x;
    x->left = _min->left;
    x->right = _min;
    _min->left = x;
    _trees_count++;

    x->parent = nullptr;
    x->mark = false;
}

template<typename DataType>
void FibonacciHeap<DataType>::_cascadingCut(FibonacciHeap::NodePtr y) {
    auto parent = y->parent;
    if (parent) {
        if (!y->mark) {
            y->mark = true;
        } else {
            _cut(y, parent);
            _cascadingCut(parent);
        }
    }
}

template<typename DataType>
void FibonacciHeap<DataType>::deleteNode(FibonacciHeap::NodePtr node) {
    if (!node) return;
    decreaseKey(node, *(reinterpret_cast<DataType*>(0)));
    extractMin();
}

template<>
void FibonacciHeap<int>::deleteNode(FibonacciHeap::NodePtr node) {
    if (!node) return;
    decreaseKey(node, -INFINITY);
    extractMin();
}

template<>
void FibonacciHeap<Student>::deleteNode(FibonacciHeap::NodePtr node) {
    if (!node) return;
    decreaseKey(node, Student("null", 0, 0));
    extractMin();
}

template<typename DataType>
void FibonacciHeap<DataType>::decreaseKey(FibonacciHeap::NodePtr node, const DataType &new_value) {
    if (!node) return;
    assert(new_value < node->data);
    node->data = new_value;

    auto parent = node->parent;
    if (parent && node->data < node->parent->data) {
        _cut(node, parent);
        _cascadingCut(parent);
    }

    if (node->data < _min->data) {
        _min = node;
    }
}

#endif //FIBONACCI_HEAP_FIBONACCI_HEAP_HXX
