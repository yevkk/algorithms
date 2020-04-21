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
        prev_leaf{nullptr},
        parent{nullptr} {}

template<typename DataType>
BPlusTree<DataType>::BPlusTree(unsigned minimum_degree) :
        _minimum_degree{minimum_degree < 2 ? 2 : minimum_degree},
        _min_node_fill{minimum_degree < 2 ? 1 : minimum_degree - 1},
        _max_node_fill{minimum_degree < 2 ? 3 : 2 * minimum_degree - 1},
        _root{(std::make_shared<BPlusNode<DataType>>())} {
    _root->leaf = true;
}

template<typename DataType>
std::pair<std::shared_ptr<BPlusNode<DataType>>, unsigned int>
BPlusTree<DataType>::_split_node(std::shared_ptr<BPlusNode<DataType>> node) {
    
}

template<typename DataType>
std::pair<std::shared_ptr<BPlusNode<DataType>>, unsigned int>
BPlusTree<DataType>::_subtree_insert(std::shared_ptr<BPlusNode<DataType>> subtree_root, const DataType &key) {
    if (subtree_root->leaf) {
        unsigned index = 0; //max index of element, smaller than key
        while (key > subtree_root->data[index]) {
            index++;
        }

        subtree_root->data.insert(index + 1, key);
        subtree_root->size++;

        if (subtree_root->size > _max_node_fill) {
            return _split_node(subtree_root);
        } else {
            return {subtree_root, index + 1};
        }

    } else {
        unsigned index = 0; //index of child where key should be insert
        while (index < subtree_root->size && key > subtree_root->data[index]) {
            index++;
        }

        _subtree_insert(subtree_root->children[index], index, key);
    }

    return std::pair<Node_ptr, unsigned int>();
}


#endif //B_PLUS_TREE_BPLUS_TREE_HXX
