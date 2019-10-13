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

    void restore_down(int index) {
        int max_child_i;
        int tmp;
        while (true) {
            if ((index * d + 1) >= size) break;
            max_child_i = -1;
            tmp = elements[index];
            for (int i = 1; i <= d; i++) {
                if (tmp < elements[index * d + i]) {
                    max_child_i = index * d + i;
                    tmp = elements[index * d + i];
                }
            }
            if (max_child_i != -1) {
                int tmp = elements[index];
                elements[index] = elements[max_child_i];
                elements[max_child_i] = tmp;

                index = max_child_i;
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

    int extract_max() {
        if (size == 0) return 0;
        if (size - 1 < capacity / 2) shrink_capacity();
        int res = elements[0];

        elements[0] = elements[size - 1];
        size--;
        restore_down(0);

        return res;
    }

    void print(int lvl = 0, int index = 0) {
        if (index >= size) return;
        for (int i = 0; i < lvl; i++) {
            std::cout << "|\t";
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
    heap.insert(21);
    heap.insert(14);
    heap.insert(7);
    heap.insert(13);
    heap.insert(2);
    heap.insert(1);
    heap.insert(12);
    heap.insert(11);
    heap.insert(9);
    heap.insert(23);
    heap.insert(26);
    heap.insert(2);

    heap.print();
    std::cout << std::endl;


    heap.extract_max();
    heap.extract_max();
    heap.extract_max();
    heap.extract_max();
    heap.extract_max();



    heap.print();


    return 0;
}