#include "bst.hpp"
#include "optimal_bst.hpp"
#include "department.hpp"

#include <iostream>
#include <vector>
#include <algorithm>

//example form Cormen's book
void example1() {
    std::vector<double> p = {15, 10, 5, 10, 20};
    std::vector<double> q = {5, 10, 5, 5, 5, 10};
    std::vector<int> data = {1, 2, 3, 4, 5};

    optimalBST(data, p, q).print();
}

//builds optimal bst using all elements from db;
//considering probability of searching all values from 60.0 to 100.0 (one digit after comma) as equal
void example2() {
    auto students = getStudentsFromDB("../../department.db");
    std::vector<Student> data;

    data.reserve(students.size());
    for (auto &e:students) {
        data.push_back(*e);
    }

    std::sort(data.begin(), data.end());
    std::vector<double> p(data.size(), (1.0 / (1000 - 599)));
    std::vector<double> q(data.size(), 0);

    q[0] = (10 * data[0].getAveragePoint() - 599) / (1000 - 599);
    for (int i = 1; i < q.size() - 1; i++) {
        q[i] = (10 * (data[i].getAveragePoint() - data[i - 1].getAveragePoint()) - 1) / (1000 - 599);
    }
    q[q.size() - 1] = (1000 - 10 * data[data.size() - 1].getAveragePoint()) / (1000 - 599);


    //Display values of data and probabilities:

//    for (auto &e:data) {
//        std::cout << e << std::endl;
//    }
//    std::cout << std::endl;
//
//    double sum = 0;
//    int i = 0;
//    for (auto &e:p) {
//        std::cout << i++ << "  " << e << std::endl;
//        sum += e;
//    }
//    std::cout << std::endl;
//
//    i = 0;
//    for (auto &e:q) {
//        std::cout << i++ << "  " << e << std::endl;
//        sum += e;
//    }
//    std::cout << std::endl;
//    std::cout << "SUM of all probabilities: " << sum << std::endl;

    // ================

    optimalBST(data, p, q).print();

}

int main() {
    example2();

    return 0;
}
