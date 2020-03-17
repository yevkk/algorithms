#ifndef SPLAY_TREE_SPLAY_TREE_HPP
#define SPLAY_TREE_SPLAY_TREE_HPP

template<typename DataType>
class BSTNode {

public:
    explicit BSTNode(DataType dataArg);

    BSTNode *left;
    BSTNode *right;
    BSTNode *parent;
    DataType data;
};

template<typename DataType>
class BST {
private:

    BSTNode<DataType> *_root;

    BSTNode<DataType> *_subtreeMin(BSTNode<DataType> *localRoot);

    BSTNode<DataType> *_subtreeMax(BSTNode<DataType> *localRoot);

    BSTNode<DataType> *_successor(BSTNode<DataType> *node);

    BSTNode<DataType> *_predecessor(BSTNode<DataType> *node);

    BSTNode<DataType> *_search(DataType &key);

    void _transplant(BSTNode<DataType> *where, BSTNode<DataType> *what);

    void _printStep(BSTNode<DataType> *node, int level);

public:
    BST();

    void insert(DataType dataArg);

    void remove(DataType &key);

    DataType min();

    DataType max();

    bool contains(DataType &key);

    void print();
};

#include "bst.hxx"

#endif //SPLAY_TREE_SPLAY_TREE_HPP
