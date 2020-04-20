#ifndef PERSISTENT_TREE_PERSISTENT_TREE_HPP
#define PERSISTENT_TREE_PERSISTENT_TREE_HPP

#include <vector>
#include <memory>
#include <ostream>

template<typename DataType>
class Node {
private:
    DataType *_data;
public:
    std::shared_ptr<Node> left;
    std::shared_ptr<Node> right;

    explicit Node(DataType *data);
    ~Node();

    DataType *data();

    void setData(DataType *data);
};

template<typename DataType>
class PersistentTree {
private:
    std::vector<std::shared_ptr<Node<DataType>>> _head_vector;
    std::vector<std::string> change_log;

    template<typename OStream>
    void _printStep(OStream &output, std::shared_ptr<Node<DataType>> node, int level);

    std::shared_ptr<Node<DataType>> _subtreeMin(std::shared_ptr<Node<DataType>> subtree_root);

    std::shared_ptr<Node<DataType>> _subtreeMax(std::shared_ptr<Node<DataType>> subtree_root);

    std::shared_ptr<Node<DataType>> _subtreeSearch(std::shared_ptr<Node<DataType>> subtree_root, const DataType &key);

    std::shared_ptr<Node<DataType>> _subtreeInsert(std::shared_ptr<Node<DataType>> subtree_root, DataType *key_ptr);

    std::shared_ptr<Node<DataType>> _subtreeDelete(std::shared_ptr<Node<DataType>> subtree_root, DataType *key_ptr);

public:
    PersistentTree();

    std::shared_ptr<Node<DataType>> head(unsigned index = 0);

    unsigned currentVersion();

    template<typename OStream>
    void printVersion(OStream &output, unsigned index);

    template<typename OStream>
    void printAll(OStream &output, bool backwards = false);

    template<typename OStream>
    void printChangeLog(OStream &output, bool backwards = false);

    DataType min();

    DataType max();

    bool includes(const DataType &key);

    void insert(DataType *key_ptr);

    void deleteNode(DataType *key_ptr);

    void clear();
};

#include "persistent_tree.hxx"

#endif //PERSISTENT_TREE_PERSISTENT_TREE_HPP
