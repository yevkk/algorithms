#include <iostream>

template <typename T>
class Node{
public:
    int key;
    T* data;
  Node(int Key, T Data){
      key = Key;
      data = Data;
  }
};

template <typename T>
class DataSet{
private:
    int capacity;

    void grow_capacity() {
        if (capacity < 100) capacity *= 4;
        else capacity *= 2;

        int *tmp = elements;
        elements = new int[capacity];
        for (int i = 0; i < size; i++)
            elements[i] = tmp[i];
        delete tmp;
    }

public:
    Node<T>* elements;
};

int main() {
    std::cout << "Hello, World!" << std::endl;
    return 0;
}