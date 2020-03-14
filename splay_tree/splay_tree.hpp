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

    void _splay(STNode<DataType> *node);

    void _rightRotate(STNode<DataType> *node);

    void _leftRotate(STNode<DataType> *node);

    STNode<DataType>* _subtreeMin(STNode<DataType>* localRoot);

    STNode<DataType>* _subtreeMax(STNode<DataType>* localRoot);

    STNode<DataType>* _successor(STNode<DataType> *node);

    STNode<DataType>* _predecessor(STNode<DataType> *node);

    void _printStep(STNode<DataType> *node, int level);

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
