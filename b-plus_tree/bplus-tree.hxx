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
void BPlusTree<DataType>::_split_node(std::shared_ptr<BPlusNode<DataType>> node) {
    unsigned split_index = (node->size / 2) + 1;
    std::vector<DataType> data_first_part(node->data.begin(), node->data.begin() + split_index);
    std::vector<DataType> data_second_part(node->data.begin() + split_index, node->data.end());

    std::vector<Node_ptr> children_first_part(node->children.begin(), node->children.begin() + split_index + 1);
    std::vector<Node_ptr> children_second_part(node->children.begin() + split_index + 1, node->children.end());
    children_second_part.push_front(nullptr);

    node->data = data_first_part;
    node->children = children_first_part;
    node->size = data_first_part.size();

    Node_ptr new_node = std::make_shared<BPlusNode<DataType>>();
    new_node->leaf = node->leaf;
    new_node->data = data_second_part;
    new_node->children = children_second_part;
    new_node->size = data_second_part.size();

    if (node->next_leaf.get()) {
        new_node->next_leaf = node->next_leaf;
        node->next_leaf->prev_leaf = new_node;
    }
    node->next_leaf = new_node;
    new_node->prev_leaf = node;

    if (!node->parent.get()) {
        Node_ptr new_parent = std::make_shared<BPlusNode<DataType>>();
        new_parent->leaf = false;
        new_parent->size = 1;
        new_parent->data.push_back(data_second_part.front());
        new_parent->children = {node, new_node};
        node->parent = new_node->parent = new_parent;
    } else {
        Node_ptr parent = node->parent;
        new_node->parent = parent;
        unsigned index = 0; //max index of element, smaller than element to insert
        while (data_second_part.front() > parent->data[index]) {
            index++;
        }

        parent->data.insert(parent->data.begin() + index + 1, data_second_part.front());
        parent->size++;

        if (index < parent->size && parent->size > _max_node_fill) {
            _split_node(parent);
        }
    }
}

template<typename DataType>
std::pair<std::shared_ptr<BPlusNode<DataType>>, unsigned int>
BPlusTree<DataType>::_subtree_insert(std::shared_ptr<BPlusNode<DataType>> subtree_root, const DataType &key) {
    if (subtree_root->leaf) {
        unsigned index = 0; //max index of element, smaller than key
        while (index < subtree_root->size && key > subtree_root->data[index]) {
            index++;
        }

        subtree_root->data.insert(subtree_root->data.begin() + index + 1, key);
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
