#ifndef B_PLUS_TREE_BPLUS_TREE_HXX
#define B_PLUS_TREE_BPLUS_TREE_HXX

#include "bplus_tree.hpp"

template<typename DataType>
BPlusNode<DataType>::BPlusNode() :
        leaf{false},
        size{0},
        data{},
        children{},
        next_leaf{nullptr},
        prev_leaf{nullptr} {}

template<typename DataType>
BPlusTree<DataType>::BPlusTree(unsigned minimum_degree) :
        _minimum_degree{minimum_degree < 2 ? 2 : minimum_degree},
        _min_node_fill{minimum_degree < 2 ? 1 : minimum_degree - 1},
        _max_node_fill{minimum_degree < 2 ? 3 : 2 * minimum_degree - 1},
        _root{} {}


#endif //B_PLUS_TREE_BPLUS_TREE_HXX
