#ifndef SPLAY_TREE_SPLAY_TREE_HXX
#define SPLAY_TREE_SPLAY_TREE_HXX

#include "splay_tree.hpp"

template<typename DataType>
SplayTree<DataType>::Node::Node(DataType dataArg) :
        left(nullptr),
        right(nullptr),
        parent(nullptr),
        data(dataArg) {}


template<typename DataType>
void SplayTree<DataType>::rightRotate(SplayTree::Node *node) {
    Node *y = node->left;

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
void SplayTree<DataType>::leftRotate(SplayTree::Node *node) {
    Node *y = node->right;

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

#endif //SPLAY_TREE_SPLAY_TREE_HXX
