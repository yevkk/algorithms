#include <iostream>

class Heap {
private:
    int size;
    int capacity;
    int d;
    int *elements;

    void grow_capacity() {
        capacity *= 2;
        int *tmp = elements;
        elements = new int[capacity];
        for (int i = 0; i < size; i++)
            elements[i] = tmp[i];
        delete tmp;
    }

    void restore_up(int index){
        int parent_i;
        while(true){
            if (index == 0) break;
            parent_i = (index-1)/d;
            if (elements[index] > elements[parent_i]){
                int tmp = elements[index];
                elements[index] = elements[parent_i];
                elements[parent_i] = tmp;

                index = parent_i;
            } else break;
        }
    }

public:
    Heap() = default;

    explicit Heap(const int &D) {
        d = D;
        size = 0;
        capacity = 1;
        elements = new int[capacity];
    }


};

int main() {
    return 0;
}