#ifndef BINOMIAL_HEAP_BINOMIAL_NODE_HPP
#define BINOMIAL_HEAP_BINOMIAL_NODE_HPP

#include "department.hpp"

template <typename DataType>
class BinomialNode {
private:
    DataType *_data;
    int _degree;
public:
    BinomialNode *parent;
    BinomialNode *sibling;
    BinomialNode *child;

    explicit BinomialNode(DataType *data);

    DataType *data();

    int degree();

    void incDegree();

    void setData(DataType *data, bool deletePrev = true);
};

#include "binomial_node.hxx"

#endif //BINOMIAL_HEAP_BINOMIAL_NODE_HPP
