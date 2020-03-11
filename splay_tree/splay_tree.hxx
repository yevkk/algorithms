#ifndef SPLAY_TREE_SPLAY_TREE_HXX
#define SPLAY_TREE_SPLAY_TREE_HXX

#include "splay_tree.hpp"

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

template<typename DataType>
void SplayTree<DataType>::splay(SplayTree::Node *node) {
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



#endif //SPLAY_TREE_SPLAY_TREE_HXX