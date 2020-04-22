#ifndef B_PLUS_TREE_BPLUS_TREE_HXX
#define B_PLUS_TREE_BPLUS_TREE_HXX

#include "bplus_tree.hpp"
#include <algorithm>

template<typename DataType>
BPlusNode<DataType>::BPlusNode() :
        leaf{false},
        size{0},
        data(),
        children(),
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
template<typename OStream>
void BPlusTree<DataType>::_printStep(OStream &output, std::shared_ptr<BPlusNode<DataType>> node, int level) {
    output << '|';
    for (int i = 0; i < level; i++) {
        output << '\t' << '|';
    }

    if (!node.get()) {
        output << "*\n";
    } else {
        output << "Data:\n";
        for (auto &item:node->data) {
            output << '|';
            for (int i = 0; i < level; i++) {
                output << '\t' << '|';
            }
            output << item << "\n";
        }

        if (!node->leaf) {
            output << '|';
            for (int i = 0; i < level; i++) {
                output << '\t' << '|';
            }
            output << "Children:\n";
            for (auto &item:node->children) {
                _printStep(output, item, level + 1);
            }
        }
    }
    output << '|';
    for (int i = 0; i < level; i++) {
        output << '\t' << '|';
    }
    output << "=====\n";
}

template<typename DataType>
template<typename OStream>
void BPlusTree<DataType>::print(OStream &output) {
    _printStep(output, _root, 0);
}

template<typename DataType>
template<typename OStream>
void BPlusTree<DataType>::printSorted(OStream &output) {
    Node_ptr ptr = _root;
    while (!ptr->leaf) {
        ptr = ptr->children[0];
    }

    int i = 0;
    while (ptr.get()) {
        for (auto &item: ptr->data) {
            output << ++i << ") " << item << "\n";
        }
        ptr = ptr->next_leaf;
    }
}

template<typename DataType>
std::pair<std::shared_ptr<BPlusNode<DataType>>, unsigned>
BPlusTree<DataType>::_subtree_search(std::shared_ptr<BPlusNode<DataType>> subtree_root, const DataType &key) {
    if (subtree_root->leaf) {
        auto it = std::find(subtree_root->data.begin(), subtree_root->data.end(), key);
        if (it != subtree_root->data.end()) {
            return {subtree_root, std::distance(subtree_root->data.begin(), it)};
        } else {
            return {nullptr, 0};
        }
    } else {
        unsigned index = 0;
        while (index < subtree_root->size && key >= subtree_root->data[index]) {
            index++;
        }
        return _subtree_search(subtree_root->children[index], key);
    }
}

template<typename DataType>
bool BPlusTree<DataType>::includes(const DataType &key) {
    return _subtree_search(_root, key).first.get();
}

template<typename DataType>
void BPlusTree<DataType>::_split_node(std::shared_ptr<BPlusNode<DataType>> node) {
    unsigned split_index = (node->size / 2);
    std::vector<DataType> data_first_part(node->data.begin(), node->data.begin() + split_index);
    std::vector<DataType> data_second_part(node->data.begin() + split_index, node->data.end());

    std::vector<Node_ptr> children_first_part(node->children.begin(), node->children.begin() + split_index + 1);
    std::vector<Node_ptr> children_second_part(node->children.begin() + split_index + 1, node->children.end());
    children_second_part.insert(children_second_part.begin(), nullptr);

    node->data = data_first_part;
    node->size = data_first_part.size();
    node->children = children_first_part;

    Node_ptr new_node = std::make_shared<BPlusNode<DataType>>();
    new_node->leaf = node->leaf;
    new_node->data = data_second_part;
    new_node->size = data_second_part.size();
    new_node->children = children_second_part;
    for (auto &item: new_node->children) {
        if (item.get()) {
            item->parent = new_node;
        }
    }

    if (!node->parent.get()) {
        Node_ptr new_parent = std::make_shared<BPlusNode<DataType>>();
        new_parent->leaf = false;
        new_parent->size = 1;
        new_parent->data = {data_second_part.front()};
        new_parent->children = {node, new_node};

        node->parent = new_parent;
        new_node->parent = new_parent;

        _root = new_parent;
    } else {
        Node_ptr parent = node->parent;
        new_node->parent = node->parent;
        unsigned index = 0; //max index of element, smaller than element to insert
        while (index < parent->size && data_second_part.front() > parent->data[index]) {
            index++;
        }

        parent->data.insert(parent->data.begin() + index, data_second_part.front());
        parent->size++;
        parent->children.insert(parent->children.begin() + index + 1, new_node);

        if (parent->size > _max_node_fill) {
            _split_node(parent);
        }
    }


    if (node->next_leaf.get()) {
        new_node->next_leaf = node->next_leaf;
        node->next_leaf->prev_leaf = new_node;
    }
    node->next_leaf = new_node;
    new_node->prev_leaf = node;
}

template<typename DataType>
std::pair<std::shared_ptr<BPlusNode<DataType>>, unsigned>
BPlusTree<DataType>::_subtree_insert(std::shared_ptr<BPlusNode<DataType>> subtree_root, const DataType &key) {
    if (subtree_root->leaf) {
        unsigned index = 0; //max index of element, smaller than key
        while (index < subtree_root->size && key > subtree_root->data[index]) {
            index++;
        }
        if (subtree_root->data.empty()) {
            subtree_root->data.push_back(key);
            subtree_root->children.push_back(Node_ptr(nullptr));
            subtree_root->children.push_back(Node_ptr(nullptr));
        } else {
            subtree_root->data.insert(subtree_root->data.begin() + index, key);
            subtree_root->children.push_back(Node_ptr(nullptr));
        }
        subtree_root->size++;

        if (subtree_root->size > _max_node_fill) {
            _split_node(subtree_root);
        }

        return {subtree_root, index};

    } else {
        unsigned index = 0; //index of child where key should be insert
        while (index < subtree_root->size && key >= subtree_root->data[index]) {
            index++;
        }

        _subtree_insert(subtree_root->children[index], key);
    }

    return std::pair<Node_ptr, unsigned int>();
}

template<typename DataType>
void BPlusTree<DataType>::insert(const DataType &key) {
    _subtree_insert(_root, key);
}

#endif //B_PLUS_TREE_BPLUS_TREE_HXX
