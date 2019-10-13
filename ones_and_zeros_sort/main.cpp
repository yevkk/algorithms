#include <iostream>

template<typename T>
class Node {
public:
    int key;
    T data;

    Node() = default;

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

    void sort1();

    void sort2();
};

template<typename T>
void DataSet<T>::grow_capacity() {
    if (capacity < 100) capacity *= 4;
    else capacity *= 2;

    Node<T> *tmp = elements;
    elements = new Node<T>[capacity];
    for (int i = 0; i < size; i++)
        elements[i] = tmp[i];
    delete tmp;
}

template<typename T>
DataSet<T>::DataSet() {
    size = 0;
    capacity = 1;
    elements = new Node<T>[capacity];
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

template<typename T>
void DataSet<T>::sort1() {
    DataSet<T> subset0, subset1;
    for (int i = 0; i < size; i++) {
        if (elements[i].key == 0)
            subset0.add_element(0, elements[i].data);
        else
            subset1.add_element(1, elements[i].data);
    }

    for (int i = 0; i < subset0.size; i++){
        elements[i] = subset0.elements[i];
    }

    for (int i = 0; i < subset1.size; i++){
        elements[subset0.size + i] = subset1.elements[i];
    }
}

int main() {
    DataSet<int> set;
    set.add_element(0, 3);
    set.add_element(1, 7);
    set.add_element(1, 4);
    set.add_element(0, 3);
    set.add_element(0, 11);
    set.add_element(1, 8);
    set.add_element(0, 13);
    set.add_element(1, 5);
    set.add_element(0, 2);
    set.print();
    set.sort1();
    set.print();

    return 0;
}