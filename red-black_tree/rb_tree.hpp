#ifndef RED_BLACK_TREE_RB_TREE_HPP
#define RED_BLACK_TREE_RB_TREE_HPP

#include "rb_node.hpp"

class RBTree {
private:
    RBNode *_root;
    RBNode *_nullNode;

    void insertFixup(RBNode *node);

    void printNode(RBNode *node, int level);

public:
    RBTree();

    void print();

    void leftRotate(RBNode *x);

    void rightRotate(RBNode *x);

    void insert(RBNode *node);
};

#endif //RED_BLACK_TREE_RB_TREE_HPP
