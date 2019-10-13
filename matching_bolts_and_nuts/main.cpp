#include <iostream>
#include <random>
#include <algorithm>
#include <ctime>


const int N = 30;

const int MAX = 200;

class Bolt {
public:
    int val;
};

class Nut {
public:
    int val;
};

bool operator<(const Bolt &bolt, const Nut &nut) { return bolt.val < nut.val; }

bool operator<(const Nut &nut, const Bolt &bolt) { return nut.val < bolt.val; }

bool operator>(const Bolt &bolt, const Nut &nut) { return nut < bolt; }

bool operator>(const Nut &nut, const Bolt &bolt) { return bolt < nut; }

bool operator<=(const Bolt &bolt, const Nut &nut) { return !(bolt > nut); }

bool operator<=(const Nut &nut, const Bolt &bolt) { return !(nut > bolt); }

bool operator>=(const Bolt &bolt, const Nut &nut) { return !(bolt < nut); }

bool operator>=(const Nut &nut, const Bolt &bolt) { return !(nut < bolt); }

bool operator==(const Bolt &bolt, const Nut &nut) { return bolt.val == nut.val; }

bool operator==(const Nut &nut, const Bolt &bolt) { return bolt == nut; }

std::ostream &operator<<(std::ostream &os, const Bolt &obj) {
    os << obj.val;
    return os;
}

std::ostream &operator<<(std::ostream &os, const Nut &obj) {
    os << obj.val;
    return os;
}

template<typename T>
class Node {
public:
    T data;
    int initial_index;
};

int rand_int(int min, int max) {
    static std::random_device rd;
    static std::seed_seq seed{rd(), static_cast<unsigned int>(time(nullptr))};
    static std::mt19937_64 gen(seed);
    std::uniform_int_distribution<int> dist(min, max);

    return dist(gen);
}

template<typename T1, typename T2>
void data_initialization(Node<T1> *A, Node<T2> *B, int size) {
    for (int i = 0; i < size; i++) {
        B[i].data.val = A[i].data.val = rand_int(0, MAX);
        B[i].initial_index = A[i].initial_index = i;
    }

    static std::random_device rd;
    static std::seed_seq seed{rd(), static_cast<unsigned int>(time(nullptr))};
    static std::mt19937_64 gen(seed);
    std::shuffle(B, B + size, gen);
}

template<typename T>
void print_array(T *A, int size) {
    for (int i = 0; i < size; i++) {
        std::cout << A[i].data << ' ';
    }
    std::cout << std::endl;
}

template<typename T1, typename T2>
int partition(T1 *A, T2 *B, int low, int high) {
    int i_pivot = (low + high) / 2;
    T1 pivot_1 = A[i_pivot];
    int i = low - 1;
    int i_tmp = 0;

    for (int j = low; j <= high; j++) {
        if (B[j].data == pivot_1.data) {
            i_tmp = j;
        } else {
            if (B[j].data < pivot_1.data) {
                i++;
                if (B[i].data == pivot_1.data) i_tmp = j;
                std::swap(B[i], B[j]);

            }
        }
    }
    std::swap(B[i + 1], B[i_tmp]);
    std::swap(A[i + 1], A[i_pivot]);

    T2 pivot_2 = B[i + 1];
    i = low - 1;
    for (int j = low; j <= high; j++) {
        if (A[j].data < pivot_2.data) {
            i++;
            std::swap(A[i], A[j]);
        }
    }
    return (i + 1);
}

template<typename T1, typename T2>
void sort_data(T1 *A, T2 *B, int low, int high) {
    if (low < high) {
        int p = partition(A, B, low, high);

        sort_data(A, B, low, p-1);
        sort_data(A, B, p + 1, high);
    }
}

int main() {
    Node<Bolt> bolts[N];
    Node<Nut> nuts[N];
    for(int i = 1; i <= 10; i++){
        std::cout << i << '.' << std::endl;

        data_initialization(bolts, nuts, N);
        print_array(bolts, N);
        print_array(nuts, N);

        std::cout << std::endl;

        sort_data(bolts, nuts, 0, N-1);
        print_array(bolts, N);
        print_array(nuts, N);

        std::cout << std::endl;
    }
    return 0;
}
