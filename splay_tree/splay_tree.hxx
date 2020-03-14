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
void SplayTree<DataType>::rightRotate(STNode<DataType> *node) {
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
void SplayTree<DataType>::leftRotate(STNode<DataType> *node) {
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
void SplayTree<DataType>::splay(STNode<DataType> *node) {
    while (node->parent) {
        if (!node->parent->parent) {
            if (node->parent->right == node) {
                leftRotate(node->parent);
            } else {
                rightRotate(node->parent);
            }
        } else if (node->parent->left == node && node->parent->parent->left == node->parent) {
            rightRotate(node->parent->parent);
            rightRotate(node->parent);
        } else if (node->parent->right == node && node->parent->parent->right == node->parent) {
            leftRotate(node->parent->parent);
            leftRotate(node->parent);
        } else if (node->parent->right == node && node->parent->parent->left == node->parent) {
            leftRotate(node->parent);
            rightRotate(node->parent);
        } else {
            rightRotate(node->parent);
            leftRotate(node->parent);
        }
    }
}

template<typename DataType>
STNode<DataType> *SplayTree<DataType>::subtreeMin(STNode<DataType> *localRoot) {
    auto ptr = localRoot;
    while (ptr->left)
        ptr = ptr->left;

    return ptr;
}

template<typename DataType>
STNode<DataType> *SplayTree<DataType>::subtreeMax(STNode<DataType> *localRoot) {
    auto ptr = localRoot;
    while (ptr->right)
        ptr = ptr->right;

    return ptr;
}

template<typename DataType>
STNode<DataType> *SplayTree<DataType>::successor(STNode<DataType> *node) {
    if (node->right)
        return subtreeMax(node);

    auto ptr = node->parent;
    while (ptr && node == ptr->right) {
        node = ptr;
        ptr = ptr->parent;
    }

    return ptr;
}

template<typename DataType>
STNode<DataType> *SplayTree<DataType>::predecessor(STNode<DataType> *node) {
    if (node->left)
        return subtreeMin(node);

    auto ptr = node->parent;
    while (ptr && node == ptr->left) {
        node = ptr;
        ptr = ptr->parent;
    }

    return ptr;
}

template<typename DataType>
void SplayTree<DataType>::printStep(STNode<DataType> *node, int level) {
    if (!node) return;

    std::cout << '|';
    for (int i = 0; i < level; i++) {
        std::cout << '\t' << '|';
    }
    std::cout << node->data << std::endl;
    printStep(node->left, level + 1);
    printStep(node->right, level + 1);
}

template<typename DataType>
DataType SplayTree<DataType>::min() {
    return subtreeMin(_root)->data;
}

template<typename DataType>
DataType SplayTree<DataType>::max() {
    return subtreeMax(_root)->data;
}

template<typename DataType>
void SplayTree<DataType>::print() {
    printStep(_root, 0);
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

    STNode<DataType> *newNode{nullptr, nullptr, prev, dataArg};
    if (!prev) {
        _root = newNode;
    } else if (dataArg > prev->data) {
        prev->right = newNode;
    } else {
        prev->left = newNode;
    };

    splay(newNode);
}


#endif //SPLAY_TREE_SPLAY_TREE_HXX