#ifndef RED_BLACK_TREE_RB_TREE_HPP
#define RED_BLACK_TREE_RB_TREE_HPP

#include <iostream>
#include "rb_node.hpp"

template<typename DataType>
class RBTree {
private:
    RBNode<DataType> *_root;
    RBNode<DataType> *_nullNode;
public:
    RBTree() {
        _root = nullptr;
        _nullNode = new RBNode<DataType>(nullptr, nullptr, nullptr, nullptr, BLACK);
        _nullNode->parent = _nullNode->left = _nullNode->right = _nullNode;
    }

    void LeftRotate(RBNode<DataType> *x) {
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

    void RightRotate(RBNode<DataType> *x) {
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

    void RBInsert(RBNode<DataType> *node) {

    }
};


#endif //RED_BLACK_TREE_RB_TREE_HPP
