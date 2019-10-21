#include "matrix.hpp"
#include <iostream>
#include <chrono>

template<typename Func>
auto time_ns(const Func &func) {
    using namespace std::chrono;
    const auto begin = system_clock::now();

    func();

    const auto end = system_clock::now();

    return duration_cast<milliseconds>(end - begin).count();
}

void benchmark(const int &n) {
    using namespace std::chrono;

    std::cout << "BENCHMARK" << std::endl;
    std::cout << "matrix size (N x N) || classic multiplication (ns) || strassen algorithm (ns)" << std::endl;

    for (int i = n; i >= 2; i -= 5) {
        Matrix A(i, i), B(i, i);
        std::cout << i << "  x " << i << " || ";

        std::cout << time_ns([&A, &B]() { matrixMultipty(A, B); }) << " || ";

        std::cout << time_ns([&A, &B]() { strassenAlgorithm(A, B); }) << std::endl;
    }
}

int main() {
    Matrix M1(20, 10);
    Matrix M2(10, 20);
    M1.print();
    std::cout << std::endl;
    M2.print();
    std::cout << std::endl;

    Matrix M3 = strassenAlgorithm(M1, M2);
    M3.print();
    std::cout << std::endl;
//    benchmark(50);
    return 0;
}