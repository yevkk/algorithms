#ifndef RED_BLACK_TREE_RB_TREE_HPP
#define RED_BLACK_TREE_RB_TREE_HPP

#include <iostream>
#include "rb_node.hpp"

template<typename DataType>
class RBTree {
private:
    RBNode<DataType> *_head;
    RBNode<DataType> *_nullNode;
public:
    RBTree() {
        _head = nullptr;
        _nullNode = RBNode<DataType>::createNullNode();
    }

 
};


#endif //RED_BLACK_TREE_RB_TREE_HPP
