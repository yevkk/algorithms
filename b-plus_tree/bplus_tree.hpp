#ifndef B_PLUS_TREE_BPLUS_TREE_HPP
#define B_PLUS_TREE_BPLUS_TREE_HPP

#include <memory>
#include <vector>

template<typename DataType>
class BPlusNode {
    typedef std::shared_ptr<BPlusNode> Node_ptr;
public:
    bool leaf;
    unsigned size;
    std::vector<DataType> data;
    std::vector<Node_ptr> children;
    Node_ptr next_leaf;
    Node_ptr prev_leaf;
    Node_ptr parent;

    BPlusNode();
};


template<typename DataType>
class BPlusTree {
    typedef std::shared_ptr<BPlusNode<DataType>> Node_ptr;
private:
    unsigned _minimum_degree;
    unsigned _min_node_fill;
    unsigned _max_node_fill;
    Node_ptr _root;

    template<typename OStream>
    void _printStep(OStream &output, Node_ptr node, int level);

    std::pair<Node_ptr, unsigned>
    _subtree_search(Node_ptr subtree_root, const DataType &key);

    void _split_node(Node_ptr node);

    std::pair<Node_ptr, unsigned>
    _subtree_insert(Node_ptr subtree_root, const DataType &key);

    void _remove_from_node(Node_ptr node, const DataType &key);

public:
    explicit BPlusTree(unsigned minimum_degree = 2);

    template<typename OStream>
    void print(OStream &output);

    template<typename OStream>
    void printSorted(OStream &output);

    bool includes(const DataType &key);

    void insert(const DataType &key);

    void remove(const DataType &key);

};


#include "bplus-tree.hxx"

#endif //B_PLUS_TREE_BPLUS_TREE_HPP
