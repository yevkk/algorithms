#include <iostream>

class Heap {
private:
    int size;
    int capacity;
    int d;
    int *elements;

    void grow_capacity() {
        if (capacity < 100) capacity *= 4;
        else capacity *= 2;

        int *tmp = elements;
        elements = new int[capacity];
        for (int i = 0; i < size; i++)
            elements[i] = tmp[i];
        delete tmp;
    }

    void shrink_capacity() {
        capacity /= 2;

        int *tmp = elements;
        elements = new int[capacity];
        for (int i = 0; i < size; i++)
            elements[i] = tmp[i];
        delete tmp;
    }

    void restore_up(int index) {
        int parent_i;
        while (true) {
            if (index == 0) break;
            parent_i = (index - 1) / d;
            if (elements[index] > elements[parent_i]) {
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

    void insert(int data) {
        if (size == capacity) grow_capacity();
        elements[size] = data;
        restore_up(size);
        size++;
    }

    void print(int lvl = 0, int index = 0) {
        if (index >= size) return;
        for (int i = 0; i < lvl; i++) {
            std::cout << '\t';
        }
        std::cout << "| " << elements[index] << std::endl;
        for (int i = 1; i <= d; i++) {
            print(lvl + 1, (d * index + i));
        }
    }
};

int main() {
    Heap heap(3);
    heap.insert(10);
    heap.insert(14);
    heap.insert(3);
    heap.insert(7);
    heap.insert(15);
    heap.insert(9);
    heap.insert(5);
    heap.insert(8);
    heap.insert(3);

    heap.print();

    return 0;
}