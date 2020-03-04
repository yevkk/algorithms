#ifndef BINOMIAL_HEAP_BINOMINAL_NODE_HPP
#define BINOMIAL_HEAP_BINOMINAL_NODE_HPP

#include "department.hpp"

class BinomialNode {
private:
    Student *_data;
    int _degree;
public:
    BinomialNode *parent;
    BinomialNode *sibling;
    BinomialNode *child;

    explicit BinomialNode(Student *data);

    Student *data();

    int degree();

    void incDegree();
};


#endif //BINOMIAL_HEAP_BINOMINAL_NODE_HPP
