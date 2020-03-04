#include "binominal_node.hpp"


BinomialNode::BinomialNode(Student *data) :
        _data(data),
        parent(nullptr),
        sibling(nullptr),
        child(nullptr),
        _degree(0) {}

Student *BinomialNode::data() {
    return _data;
}

int BinomialNode::degree() {
    return _degree;
}

void BinomialNode::incDegree() {
    _degree++;
}
