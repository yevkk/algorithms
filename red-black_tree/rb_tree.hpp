#ifndef RED_BLACK_TREE_RB_TREE_HPP
#define RED_BLACK_TREE_RB_TREE_HPP

#include "rb_node.hpp"

class RBTree {
private:
    RBNode *_root;
    RBNode *_nullNode;

    void insertFixup(RBNode *node);

    void deleteFixup(RBNode *node);

    void transplant(RBNode *dst, RBNode *src);

    void printNode(RBNode *node, int level);

public:
    RBTree();

    void print();

    RBNode *min(RBNode *root);

    RBNode *max(RBNode *root);

    RBNode *successor(RBNode *node);

    RBNode *predecessor(RBNode *node);

    RBNode *search(RBNode *root, Student key);

    void leftRotate(RBNode *x);

    void rightRotate(RBNode *x);

    void insertNode(RBNode *node);

    void deleteNode(RBNode *node);
};

#endif //RED_BLACK_TREE_RB_TREE_HPP
