#ifndef SPLAY_TREE_SPLAY_TREE_HPP
#define SPLAY_TREE_SPLAY_TREE_HPP

template<typename DataType>
class SplayTree {
private:
    class Node {
    public:
        Node *left;
        Node *right;
        Node *parent;
        DataType data;

        explicit Node(DataType dataArg);
    };

    Node *root;

    void splay(Node *node);

    void rightRotate(Node *node);

    void leftRotate(Node *node);

public:
    void insert(DataType dataArg);

    void remove(Node *node);

    DataType min();

    DataType max();
};


#include "splay_tree.hxx"

#endif //SPLAY_TREE_SPLAY_TREE_HPP
