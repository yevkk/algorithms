#include "rb_tree.hpp"

template<typename DataType>
RBTree<DataType>::RBTree() {
    _root = nullptr;
    _nullNode = new RBNode<DataType>(nullptr, nullptr, nullptr, nullptr, BLACK);
    _nullNode->parent = _nullNode->left = _nullNode->right = _nullNode;
}

template<typename DataType>
void RBTree<DataType>::LeftRotate(RBNode<DataType> *x) {
    RBNode<DataType> *y = x->right;
    x->right = y->left;

    if (y->left != _nullNode) {
        y->left->parent = x;
    }
    y->parent = x->parent;
    if (x->parent == _nullNode) {
        _root = y;
    } else if (x == x->parent->left) {
        x->parent->left = y;
    } else {
        x->parent->right = y;
    }
    y->left = x;
    x->parent = y;
}

template<typename DataType>
void RBTree<DataType>::RightRotate(RBNode<DataType> *x) {
    RBNode<DataType> *y = x->left;
    x->left = y->right;

    if (y->right != _nullNode) {
        y->right->parent = x;
    }
    y->parent = x->parent;
    if (x->parent == _nullNode) {
        _root = y;
    } else if (x == x->parent->left) {
        x->parent->left = y;
    } else {
        x->parent->right = y;
    }
    y->right = x;
    x->parent = y;
}

template<typename DataType>
void RBTree<DataType>::RBInsert(RBNode<DataType> *node) {
    RBNode<DataType> *y = _nullNode, *x = _root;
    while (x != _nullNode) {
        y = x;
        if (node->data() < x->data()) {
            x = x->left;
        } else {
            x = x->right;
        }
    }
    node->parent = y;
    if (y == _nullNode) {
        _root = node;
    } else if (node->data() < y->data()) {
        y->left = node;
    } else {
        y->right = node;
    }
    node->left = node->right = _nullNode;
    node->setColor(RED);
    RBInsertFixup(node);
}