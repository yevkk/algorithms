#ifndef RED_BLACK_TREE_RB_TREE_HPP
#define RED_BLACK_TREE_RB_TREE_HPP

#include <iostream>
#include "rb_node.hpp"

template<typename DataType>
class RBTree {
private:
    RBNode<DataType> *_root;
    RBNode<DataType> *_nullNode;

    void RBInsertFixup(RBNode<DataType> *x) {

    }

public:
    RBTree();

    void LeftRotate(RBNode<DataType> *x);

    void RightRotate(RBNode<DataType> *x);

    void RBInsert(RBNode<DataType> *node);
};


#endif //RED_BLACK_TREE_RB_TREE_HPP
