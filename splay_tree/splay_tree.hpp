#ifndef SPLAY_TREE_SPLAY_TREE_HPP
#define SPLAY_TREE_SPLAY_TREE_HPP

template<typename DataType>
class STNode {

public:
    explicit STNode(DataType dataArg);

    STNode *left;
    STNode *right;
    STNode *parent;
    DataType data;
};

template<typename DataType>
class SplayTree {
private:

    STNode<DataType> *_root;

    void splay(STNode<DataType> *node);

    void rightRotate(STNode<DataType> *node);

    void leftRotate(STNode<DataType> *node);

    STNode<DataType>* subtreeMin(STNode<DataType>* localRoot);

    STNode<DataType>* subtreeMax(STNode<DataType>* localRoot);

    STNode<DataType>* successor(STNode<DataType> *node);

    STNode<DataType>* predecessor(STNode<DataType> *node);

    void printStep(STNode<DataType> *node, int level);

public:
    SplayTree();

    void insert(DataType dataArg);

    void remove(STNode<DataType> *node);

    DataType min();

    DataType max();

    void print();
};



#include "splay_tree.hxx"

#endif //SPLAY_TREE_SPLAY_TREE_HPP
