#include <iostream>
#include <ctime>
#include <random>

class Heap {
private:
    int size;
    int capacity;
    int d;
    int *elements;

    void grow_capacity() {
        int c = capacity;
        if (capacity < 100) capacity *= 4;
        else capacity *= 2;

        int *tmp = elements;
        elements = new int[capacity];
        std::copy(tmp + 0, tmp + c, elements);
        delete[] tmp;
    }

    void shrink_capacity() {
        int c = capacity;
        capacity /= 2;

        int *tmp = elements;
        elements = new int[capacity];
        std::copy(tmp + 0, tmp + c, elements);
        delete[] tmp;
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

    void increase_key(int key, int step, int index = 0) {
        if (index >= size) return;
        if (elements[index] == key) {
            elements[index] += step;
            restore_up(index);
            return;
        }
        for (int i = 1; i <= d; i++) {
            if (elements[index * d + i] >= key)
                increase_key(key, step, index * d + i);
        }
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

int rand_int(int min, int max) {
    static std::random_device rd;
    static std::seed_seq seed{rd(), static_cast<unsigned int>(time(nullptr))};
    static std::mt19937_64 gen(seed);
    std::uniform_int_distribution<int> dist(min, max);

    return dist(gen);
}

const int P = 15;

int main() {
    Heap heap(4);
    for (int i = 0; i < P; i++)
        heap.insert(rand_int(0, 20));

    heap.print();
    std::cout << std::endl;

    heap.increase_key(10, 50);
    heap.increase_key(15, 50);
    heap.increase_key(17, 50);
    heap.increase_key(18, 50);

    heap.print();
    std::cout << std::endl;

    int array[P];

    for (auto &e:array)
        e = heap.extract_max();

    for (auto &e:array)
        std::cout << e << "  ";

    return 0;
}