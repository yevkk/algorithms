#ifndef SPLAY_TREE_SPLAY_TREE_HXX
#define SPLAY_TREE_SPLAY_TREE_HXX

#include "splay_tree.hpp"
#include <iostream>

template<typename DataType>
STNode<DataType>::STNode(DataType dataArg) :
        left(nullptr),
        right(nullptr),
        parent(nullptr),
        data(dataArg) {}

template<typename DataType>
SplayTree<DataType>::SplayTree() :
        _root(nullptr) {}

template<typename DataType>
void SplayTree<DataType>::_rightRotate(STNode<DataType> *node) {
    STNode<DataType> *y = node->left;

    if (y) {
        node->left = y->right;

        if (y->right) {
            y->right->parent = node;
        }
        y->parent = node->parent;
    }
    if (!node->parent) {
        _root = y;
    } else if (node == node->parent->left) {
        node->parent->left = y;
    } else {
        node->parent->right = y;
    }
    y->right = node;
    node->parent = y;
}

template<typename DataType>
void SplayTree<DataType>::_leftRotate(STNode<DataType> *node) {
    STNode<DataType> *y = node->right;

    if (y) {
        node->right = y->left;

        if (y->left) {
            y->left->parent = node;
        }
        y->parent = node->parent;
    }
    if (!node->parent) {
        _root = y;
    } else if (node == node->parent->left) {
        node->parent->left = y;
    } else {
        node->parent->right = y;
    }
    y->left = node;
    node->parent = y;
}

template<typename DataType>
void SplayTree<DataType>::_splay(STNode<DataType> *node) {
    while (node->parent) {
        if (!node->parent->parent) {
            if (node->parent->right == node) {
                _leftRotate(node->parent);
            } else {
                _rightRotate(node->parent);
            }
        } else if (node->parent->left == node && node->parent->parent->left == node->parent) {
            _rightRotate(node->parent->parent);
            _rightRotate(node->parent);
        } else if (node->parent->right == node && node->parent->parent->right == node->parent) {
            _leftRotate(node->parent->parent);
            _leftRotate(node->parent);
        } else if (node->parent->right == node && node->parent->parent->left == node->parent) {
            _leftRotate(node->parent);
            _rightRotate(node->parent);
        } else {
            _rightRotate(node->parent);
            _leftRotate(node->parent);
        }
    }
}

template<typename DataType>
STNode<DataType> *SplayTree<DataType>::_subtreeMin(STNode<DataType> *localRoot) {
    auto ptr = localRoot;
    while (ptr->left)
        ptr = ptr->left;

    return ptr;
}

template<typename DataType>
STNode<DataType> *SplayTree<DataType>::_subtreeMax(STNode<DataType> *localRoot) {
    auto ptr = localRoot;
    while (ptr->right)
        ptr = ptr->right;

    return ptr;
}

template<typename DataType>
STNode<DataType> *SplayTree<DataType>::_successor(STNode<DataType> *node) {
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
STNode<DataType> *SplayTree<DataType>::_predecessor(STNode<DataType> *node) {
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
void SplayTree<DataType>::_printStep(STNode<DataType> *node, int level) {
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
DataType SplayTree<DataType>::min() {
    return _subtreeMin(_root)->data;
}

template<typename DataType>
DataType SplayTree<DataType>::max() {
    return _subtreeMax(_root)->data;
}

template<typename DataType>
void SplayTree<DataType>::print() {
    _printStep(_root, 0);
}

template<typename DataType>
void SplayTree<DataType>::insert(DataType dataArg) {
    STNode<DataType> *prev = nullptr;
    STNode<DataType> *ptr = _root;

    while (ptr) {
        prev = ptr;

        if (dataArg > ptr->data) {
            ptr = ptr->right;
        } else {
            ptr = ptr->left;
        }
    }

    STNode<DataType> *newNode = new STNode<DataType>(dataArg);
    newNode->left = newNode->right = nullptr;
    newNode->parent = prev;

    if (!prev) {
        _root = newNode;
    } else if (dataArg > prev->data) {
        prev->right = newNode;
    } else {
        prev->left = newNode;
    };

    _splay(newNode);
}

template<typename DataType>
STNode<DataType> *SplayTree<DataType>::_search(DataType &key) {
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
bool SplayTree<DataType>::contains(DataType &key) {
    return _search(key) != nullptr;
}

template<typename DataType>
void SplayTree<DataType>::_transplant(STNode<DataType> *where, STNode<DataType> *what) {
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
void SplayTree<DataType>::remove(DataType &key) {
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

            _splay(ptr);
        }

        delete forDelete;
    }
}

template<typename DataType>
void SplayTree<DataType>::join(SplayTree<DataType> &tree) {
    if (this->min() > tree.max()) {
        tree._splay(tree._subtreeMax(tree._root));
        tree._root->right = _root;
        _root = tree._root;
    } else if (this->max() < tree.min()) {
        this->_splay(this->_subtreeMax(this->_root));
        _root->right = tree._root;
    }
}

template<typename DataType>
SplayTree<DataType> SplayTree<DataType>::split(DataType &key) {
    _splay(_search(key));
    SplayTree<DataType> tree;
    tree._root = _root->right;
    _root->right = nullptr;

    return tree;
}


#endif //SPLAY_TREE_SPLAY_TREE_HXX