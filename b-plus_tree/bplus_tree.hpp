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
    std::vector<DataType *> data;
    std::vector<Node_ptr> children;
    Node_ptr next_leaf;
    Node_ptr prev_leaf;

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

public:
    explicit BPlusTree(unsigned minimum_degree = 2);
};


#include "bplus-tree.hxx"

#endif //B_PLUS_TREE_BPLUS_TREE_HPP
