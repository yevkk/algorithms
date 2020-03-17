#ifndef SPLAY_TREE_SPLAY_TREE_HXX
#define SPLAY_TREE_SPLAY_TREE_HXX

#include "bst.hpp"
#include <iostream>

template<typename DataType>
BSTNode<DataType>::BSTNode(DataType dataArg) :
        left(nullptr),
        right(nullptr),
        parent(nullptr),
        data(dataArg) {}

template<typename DataType>
BST<DataType>::BST() :
        _root(nullptr) {}


template<typename DataType>
BSTNode<DataType> *BST<DataType>::_subtreeMin(BSTNode<DataType> *localRoot) {
    auto ptr = localRoot;
    while (ptr->left)
        ptr = ptr->left;

    return ptr;
}

template<typename DataType>
BSTNode<DataType> *BST<DataType>::_subtreeMax(BSTNode<DataType> *localRoot) {
    auto ptr = localRoot;
    while (ptr->right)
        ptr = ptr->right;

    return ptr;
}

template<typename DataType>
BSTNode<DataType> *BST<DataType>::_successor(BSTNode<DataType> *node) {
    if (node->right)
        return _subtreeMax(node);

    auto ptr = node->parent;
    while (ptr && node == ptr->right) {
        node = ptr;
        ptr = ptr->parent;
    }

    return ptr;
}

template<typename DataType>
BSTNode<DataType> *BST<DataType>::_predecessor(BSTNode<DataType> *node) {
    if (node->left)
        return _subtreeMin(node);

    auto ptr = node->parent;
    while (ptr && node == ptr->left) {
        node = ptr;
        ptr = ptr->parent;
    }

    return ptr;
}

template<typename DataType>
void BST<DataType>::_printStep(BSTNode<DataType> *node, int level) {
    std::cout << '|';
    for (int i = 0; i < level; i++) {
        std::cout << '\t' << '|';
    }
    if (!node) {
        std::cout << '*' << std::endl;
    } else {
        std::cout << node->data << std::endl;
        _printStep(node->left, level + 1);
        _printStep(node->right, level + 1);
    }
}

template<typename DataType>
DataType BST<DataType>::min() {
    return _subtreeMin(_root)->data;
}

template<typename DataType>
DataType BST<DataType>::max() {
    return _subtreeMax(_root)->data;
}

template<typename DataType>
void BST<DataType>::print() {
    _printStep(_root, 0);
}

template<typename DataType>
void BST<DataType>::insert(DataType dataArg) {
    BSTNode<DataType> *prev = nullptr;
    BSTNode<DataType> *ptr = _root;

    while (ptr) {
        prev = ptr;

        if (dataArg > ptr->data) {
            ptr = ptr->right;
        } else {
            ptr = ptr->left;
        }
    }

    auto *newNode = new BSTNode<DataType>(dataArg);
    newNode->left = newNode->right = nullptr;
    newNode->parent = prev;

    if (!prev) {
        _root = newNode;
    } else if (dataArg > prev->data) {
        prev->right = newNode;
    } else {
        prev->left = newNode;
    };

}

template<typename DataType>
BSTNode<DataType> *BST<DataType>::_search(DataType &key) {
    auto ptr = _root;

    while (ptr) {
        if (key == ptr->data) {
            _splay(ptr);
            return ptr;
        }

        if (key < ptr->data) {
            ptr = ptr->left;
        } else if (key > ptr->data) {
            ptr = ptr->right;
        }
    }

    return nullptr;
}

template<typename DataType>
bool BST<DataType>::contains(DataType &key) {
    return _search(key) != nullptr;
}

template<typename DataType>
void BST<DataType>::_transplant(BSTNode<DataType> *where, BSTNode<DataType> *what) {
    if (!where->parent) {
        _root = what;
    } else if (where == where->parent->left) {
        where->parent->left = what;
    } else {
        where->parent->right = what;
    }

    if (what) {
        what->parent = where->parent;
    }
}

template<typename DataType>
void BST<DataType>::remove(DataType &key) {
    auto forDelete = _search(key);

    if (forDelete) {
        if (!forDelete->right) {
            _transplant(forDelete, forDelete->left);
        } else if (!forDelete->left) {
            _transplant(forDelete, forDelete->right);
        } else {
            auto ptr = _subtreeMin(forDelete->right);

            if (ptr->parent != forDelete) {
                _transplant(ptr, ptr->right);
                ptr->right = forDelete->right;
                ptr->parent = forDelete->left;
            }

            _transplant(forDelete, ptr);

            ptr->left = forDelete->left;
            ptr->left->parent = ptr;
        }

        delete forDelete;
    }
}

#endif //SPLAY_TREE_SPLAY_TREE_HXX