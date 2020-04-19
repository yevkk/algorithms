#include "persistent_tree.hpp"

#include <cassert>

template<typename DataType>
Node<DataType>::Node(DataType *data) :
        _data{data},
        left{nullptr},
        right{nullptr} {};

template<typename DataType>
DataType *Node<DataType>::data() {
    return _data;
};

template<typename DataType>
Node<DataType> *PersistentTree<DataType>::_head(unsigned index) {
    assert(index < _head_vector.size - 1 && "Out of range");
    return _head_vector[index];
}

template<typename DataType>
PersistentTree<DataType>::PersistentTree() {
    _head_vector.push_back(nullptr);
}

template<typename DataType>
unsigned PersistentTree<DataType>::currentVersion() {
    return _head_vector.size() - 1;
}

template<typename DataType>
template<typename OStream>
void PersistentTree<DataType>::_printStep(OStream &output, Node<DataType> *node, int level) {
    output << '|';
    for (int i = 0; i < level; i++) {
        output << '\t' << '|';
    }

    if (!node) {
        output << '*' << std::endl;
    } else {
        output << osRank(node) << "| ";
        output << *(node->data()) << "   (c:" << node->color() << ", s:" << node->size << ")" << std::endl;
        printStep(output, node->left, level + 1);
        printStep(output, node->right, level + 1);
    }
}

template<typename DataType>
template<typename OStream>
void PersistentTree<DataType>::printVersion(OStream &output, unsigned index) {
    assert(index < _head_vector.size - 1 && "Out of range");
    _printStep(output, _head_vector[index], 0);
}

template<typename DataType>
template<typename OStream>
void PersistentTree<DataType>::printAll(OStream &output, bool backwards) {
    int index = backwards ? currentVersion() : 0;
    int termination_value = backwards ? -1 : currentVersion() + 1;

    while (index != termination_value) {
        output << "[VERSION " << index << "]\n";
        printVersion(output, index);
        output << '\n';
        backwards ? index-- : index++;
    }
}

template<typename DataType>
Node<DataType> *PersistentTree<DataType>::_subtreeMin(Node<DataType> *subtree_root) {
    Node<DataType> *ptr = subtree_root;
    while (ptr->left) {
        ptr = ptr->left;
    }
    return ptr;
}

template<typename DataType>
Node<DataType> *PersistentTree<DataType>::_subtreeMax(Node<DataType> *subtree_root) {
    Node<DataType> *ptr = subtree_root;
    while (ptr->right) {
        ptr = ptr->right;
    }
    return ptr;
}

template<typename DataType>
DataType PersistentTree<DataType>::min() {
    return _subtreeMin(_head_vector.back())->data();
}

template<typename DataType>
DataType PersistentTree<DataType>::max() {
    return _subtreeMax(_head_vector.back())->data();
}

template<typename DataType>
Node<DataType> *PersistentTree<DataType>::_subtreeSearch(Node<DataType> *subtree_root, const DataType &key) {
    if ((!subtree_root) || (key == *(subtree_root->data()))) {
        return subtree_root;
    }
    if (key < *(subtree_root->data())) {
        return _subtreeSearch(subtree_root->left, key);
    } else {
        return _subtreeSearch(subtree_root->right, key);
    }
}

template<typename DataType>
bool PersistentTree<DataType>::includes(const DataType &key) {
    return _subtreeSearch(_head_vector.back(), key);
}

template<typename DataType>
Node<DataType> *PersistentTree<DataType>::_subtreeInsert(Node<DataType> *subtree_root, DataType *key_ptr) {
    if (!subtree_root) return new Node<DataType>(key_ptr);

    Node<DataType> *updated_root{subtree_root->data()};
    if (*key_ptr < *(subtree_root->data())) {
        updated_root->left = _subtreeInsert(subtree_root->left, key_ptr);
        updated_root->right = subtree_root->right;
    } else {
        updated_root->left = subtree_root->left;
        updated_root->right = _subtreeInsert(subtree_root->right, key_ptr);
    }

    return updated_root;
}




