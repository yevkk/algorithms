#include <iostream>

template<typename T>
class Node {
public:
    int key;
    T *data;

    Node(int Key, T Data) {
        key = Key;
        data = Data;
    }
};

template<typename T>
class DataSet {
private:
    int capacity;

    void grow_capacity();

public:
    int size;
    Node<T> *elements;

    DataSet();

    void add_element(int key, T data);

    void print();
};

template<typename T>
void DataSet<T>::grow_capacity() {
    if (capacity < 100) capacity *= 4;
    else capacity *= 2;

    int *tmp = elements;
    elements = new int[capacity];
    for (int i = 0; i < size; i++)
        elements[i] = tmp[i];
    delete tmp;
}

template<typename T>
DataSet<T>::DataSet() {
    size = 0;
    capacity = 1;
    elements = new T[capacity];
}

template<typename T>
void DataSet<T>::add_element(int key, T data) {
    if (size == capacity) grow_capacity();
    elements[size] = {key, data};
    size++;
}

template<typename T>
void DataSet<T>::print() {
    for (int i = 0; i < size; i++)
        std::cout << elements[i].data << '(' << elements[i].key << ')' << "  ";
    std::cout << std::endl;
}

int main() {
    return 0;
}