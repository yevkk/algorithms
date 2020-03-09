#ifndef SPLAY_TREE_SPLAY_TREE_HXX
#define SPLAY_TREE_SPLAY_TREE_HXX

#include "splay_tree.hpp"

template<typename DataType>
SplayTree<DataType>::Node::Node(DataType dataArg) :
        left(nullptr),
        right(nullptr),
        parent(nullptr),
        data(dataArg) {}

#endif //SPLAY_TREE_SPLAY_TREE_HXX
