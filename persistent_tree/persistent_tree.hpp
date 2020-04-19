#ifndef PERSISTENT_TREE_PERSISTENT_TREE_HPP
#define PERSISTENT_TREE_PERSISTENT_TREE_HPP

#include <vector>
#include <ostream>

template<typename DataType>
class Node {
private:
    DataType *_data;
public:
    Node *left;
    Node *right;

    explicit Node(DataType *data);

    DataType *data();
};

template<typename DataType>
class PersistentTree {
private:
    std::vector<Node<DataType> *> _head_vector;

    Node<DataType> *_head(unsigned index = 0);

    template<typename OStream>
    void _printStep(OStream &output, Node<DataType> *node, int level);

    Node<DataType> *_subtreeMin(Node<DataType> *subtree_root);

    Node<DataType> *_subtreeMax(Node<DataType> *subtree_root);

    Node<DataType> *_subtreeSearch(Node<DataType> *subtree_root, const DataType &key);

    Node<DataType> *_subtreeInsert(Node<DataType> *subtree_root, DataType *key_ptr);

public:
    PersistentTree();

    unsigned currentVersion();

    template<typename OStream>
    void printVersion(OStream &output, unsigned index);

    template<typename OStream>
    void printAll(OStream &output, bool backwards = false);

    DataType min();

    DataType max();

    bool includes(const DataType &key);


};


#endif //PERSISTENT_TREE_PERSISTENT_TREE_HPP
