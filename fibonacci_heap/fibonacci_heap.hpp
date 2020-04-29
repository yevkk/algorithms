#ifndef FIBONACCI_HEAP_FIBONACCI_HEAP_HPP
#define FIBONACCI_HEAP_FIBONACCI_HEAP_HPP

#include <memory>

//FB - fibonacci heap
template<typename DataType>
class FBNode {
public:
    DataType data;

    std::shared_ptr<FBNode> parent;
    std::shared_ptr<FBNode> child;

    std::shared_ptr<FBNode> left;
    std::shared_ptr<FBNode> right;

    unsigned degree;
    bool mark;

    explicit FBNode(const DataType &data);

    ~FBNode() = default;
};

template<typename DataType>
class FibonacciHeap {
    typedef std::shared_ptr<FBNode<DataType>> NodePtr;
private:
    NodePtr _min;
    unsigned _n; //amount of nodes in heap;
    unsigned _trees_count;

    template<typename OStream>
    void _printStep(OStream &output, NodePtr node, unsigned level_size, unsigned level);

public:
    FibonacciHeap();

    template<typename OStream>
    void print(OStream &output);

    void insert(const DataType &key);

    DataType min();

    template<typename T>
    friend FibonacciHeap<T> heapUnion(FibonacciHeap<T> *heapL, FibonacciHeap<T> *heapR);
};

/*
 * @note deletes heapL and heapR;
 */


#include "fibonacci_heap.hxx"

#endif //FIBONACCI_HEAP_FIBONACCI_HEAP_HPP
