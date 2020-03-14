#ifndef SPLAY_TREE_SPLAY_TREE_HXX
#define SPLAY_TREE_SPLAY_TREE_HXX

#include "splay_tree.hpp"
#include <iostream>

template<typename DataType>
STNode<DataType>::STNode(DataType dataArg) :
        left(nullptr),
        right(nullptr),
        parent(nullptr),
        data(dataArg) {}

template<typename DataType>
SplayTree<DataType>::SplayTree() :
        _root(nullptr) {}

template<typename DataType>
void SplayTree<DataType>::_rightRotate(STNode<DataType> *node) {
    STNode<DataType> *y = node->left;

    if (y) {
        node->left = y->right;

        if (y->right) {
            y->right->parent = node;
        }
        y->parent = node->parent;
    }
    if (!node->parent) {
        _root = y;
    } else if (node == node->parent->left) {
        node->parent->left = y;
    } else {
        node->parent->right = y;
    }
    y->right = node;
    node->parent = y;
}

template<typename DataType>
void SplayTree<DataType>::_leftRotate(STNode<DataType> *node) {
    STNode<DataType> *y = node->right;

    if (y) {
        node->right = y->left;

        if (y->left) {
            y->left->parent = node;
        }
        y->parent = node->parent;
    }
    if (!node->parent) {
        _root = y;
    } else if (node == node->parent->left) {
        node->parent->left = y;
    } else {
        node->parent->right = y;
    }
    y->left = node;
    node->parent = y;
}

template<typename DataType>
void SplayTree<DataType>::_splay(STNode<DataType> *node) {
    while (node->parent) {
        if (!node->parent->parent) {
            if (node->parent->right == node) {
                _leftRotate(node->parent);
            } else {
                _rightRotate(node->parent);
            }
        } else if (node->parent->left == node && node->parent->parent->left == node->parent) {
            _rightRotate(node->parent->parent);
            _rightRotate(node->parent);
        } else if (node->parent->right == node && node->parent->parent->right == node->parent) {
            _leftRotate(node->parent->parent);
            _leftRotate(node->parent);
        } else if (node->parent->right == node && node->parent->parent->left == node->parent) {
            _leftRotate(node->parent);
            _rightRotate(node->parent);
        } else {
            _rightRotate(node->parent);
            _leftRotate(node->parent);
        }
    }
}

template<typename DataType>
STNode<DataType> *SplayTree<DataType>::_subtreeMin(STNode<DataType> *localRoot) {
    auto ptr = localRoot;
    while (ptr->left)
        ptr = ptr->left;

    return ptr;
}

template<typename DataType>
STNode<DataType> *SplayTree<DataType>::_subtreeMax(STNode<DataType> *localRoot) {
    auto ptr = localRoot;
    while (ptr->right)
        ptr = ptr->right;

    return ptr;
}

template<typename DataType>
STNode<DataType> *SplayTree<DataType>::_successor(STNode<DataType> *node) {
    if (node->right)
        return _subtreeMax(node);

    auto ptr = node->parent;
    while (ptr && node == ptr->right) {
        node = ptr;
        ptr = ptr->parent;
    }

    return ptr;
}

template<typename DataType>
STNode<DataType> *SplayTree<DataType>::_predecessor(STNode<DataType> *node) {
    if (node->left)
        return _subtreeMin(node);

    auto ptr = node->parent;
    while (ptr && node == ptr->left) {
        node = ptr;
        ptr = ptr->parent;
    }

    return ptr;
}

template<typename DataType>
void SplayTree<DataType>::_printStep(STNode<DataType> *node, int level) {
    if (!node) return;

    std::cout << '|';
    for (int i = 0; i < level; i++) {
        std::cout << '\t' << '|';
    }
    std::cout << node->data << std::endl;
    _printStep(node->left, level + 1);
    _printStep(node->right, level + 1);
}

template<typename DataType>
DataType SplayTree<DataType>::min() {
    return _subtreeMin(_root)->data;
}

template<typename DataType>
DataType SplayTree<DataType>::max() {
    return _subtreeMax(_root)->data;
}

template<typename DataType>
void SplayTree<DataType>::print() {
    _printStep(_root, 0);
}

template<typename DataType>
void SplayTree<DataType>::insert(DataType dataArg) {
    STNode<DataType> *prev = nullptr;
    STNode<DataType> *ptr = _root;

    while (ptr) {
        prev = ptr;

        if (dataArg > ptr->data) {
            ptr = ptr->right;
        } else {
            ptr = ptr->left;
        }
    }

    STNode<DataType> *newNode = new STNode<DataType>(dataArg);
    newNode->left = newNode->right = nullptr;
    newNode->parent = prev;

    if (!prev) {
        _root = newNode;
    } else if (dataArg > prev->data) {
        prev->right = newNode;
    } else {
        prev->left = newNode;
    };

    _splay(newNode);
}


#endif //SPLAY_TREE_SPLAY_TREE_HXX