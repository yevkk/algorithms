#ifndef PERSISTENT_TREE_PERSISTENT_TREE_HXX
#define PERSISTENT_TREE_PERSISTENT_TREE_HXX

#include <cassert>
#include <sstream>
#include "persistent_tree.hpp"


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
void Node<DataType>::setData(DataType *data) {
    _data = data;
};

template<typename DataType>
Node<DataType> *PersistentTree<DataType>::head(unsigned index) {
    assert(index <= _head_vector.size - 1 && "Out of range");
    return _head_vector[index];
}

template<typename DataType>
PersistentTree<DataType>::PersistentTree() {
    _head_vector.push_back(nullptr);
    change_log.push_back("Tree created");
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
        output << *(node->data()) << std::endl;
        _printStep(output, node->left, level + 1);
        _printStep(output, node->right, level + 1);
    }
}

template<typename DataType>
template<typename OStream>
void PersistentTree<DataType>::printVersion(OStream &output, unsigned index) {
    assert(index <= _head_vector.size() - 1 && "Out of range");
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
template<typename OStream>
void PersistentTree<DataType>::printChangeLog(OStream &output, bool backwards) {
    output << "CHANGE LOG:\n";

    int index = backwards ? currentVersion() : 0;
    int termination_value = backwards ? -1 : currentVersion() + 1;

    while (index != termination_value) {
        output << "[VERSION " << index << "]\t" << change_log[index] << '\n';
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

    auto updated_root = new Node<DataType>(subtree_root->data());
    if (*key_ptr < *(subtree_root->data())) {
        updated_root->left = _subtreeInsert(subtree_root->left, key_ptr);
        updated_root->right = subtree_root->right;
    } else {
        updated_root->left = subtree_root->left;
        updated_root->right = _subtreeInsert(subtree_root->right, key_ptr);
    }

    return updated_root;
}

template<typename DataType>
void PersistentTree<DataType>::insert(DataType *key_ptr) {
    _head_vector.push_back(_subtreeInsert(_head_vector.back(), key_ptr));
    std::stringstream str;
    str << "Inserted item " << *key_ptr << ";";
    change_log.push_back(str.str());
}

template<typename DataType>
Node<DataType> *PersistentTree<DataType>::_subtreeDelete(Node<DataType> *subtree_root, DataType *key_ptr) {
    if (!subtree_root) return subtree_root;

    auto updated_root = new Node<DataType>(subtree_root->data());
    if (*key_ptr < *(subtree_root->data())) {
        updated_root->left = _subtreeDelete(subtree_root->left, key_ptr);
        updated_root->right = subtree_root->right;
    } else if (*key_ptr > *(subtree_root->data())) {
        updated_root->left = subtree_root->left;
        updated_root->right = _subtreeDelete(subtree_root->right, key_ptr);
    } else {
        if (!subtree_root->left) {
            return subtree_root->right;;
        }

        if (!subtree_root->right) {
            return subtree_root->left;;
        }

        auto tmp = _subtreeMin(subtree_root->right);
        updated_root->setData(tmp->data());
        updated_root->right = _subtreeDelete(subtree_root->right, tmp->data());
        updated_root->left = subtree_root->left;
    }

    return updated_root;
}

template<typename DataType>
void PersistentTree<DataType>::deleteNode(DataType *key_ptr) {
    _head_vector.push_back(_subtreeDelete(_head_vector.back(), key_ptr));
    std::stringstream str;
    str << "Deleted item " << *key_ptr << ";";
    change_log.push_back(str.str());
}

template<typename DataType>
void PersistentTree<DataType>::_subtreeClear(Node<DataType> *subtree_root) {
    if (subtree_root) {
        if (dynamic_cast<Node<DataType> *>(subtree_root->left)) _subtreeClear(subtree_root->left);
        if (dynamic_cast<Node<DataType> *>(subtree_root->right)) _subtreeClear(subtree_root->right);
        delete (subtree_root);
    }
}

template<typename DataType>
void PersistentTree<DataType>::clear() {
    for (auto &item: _head_vector) {
        _subtreeClear(item);
    }
    _head_vector.clear();
    _head_vector.push_back(nullptr);
    change_log.push_back("Tree cleared;");
}

#endif //PERSISTENT_TREE_PERSISTENT_TREE_HXX
