#ifndef BINOMIAL_HEAP_INFNULL_HPP
#define BINOMIAL_HEAP_INFNULL_HPP

#include "department.hpp"
#include <vector>
#include <string>
#include <iostream>

template<typename T>
struct inf;

template<>
struct inf<int> {
    static constexpr int value = INT_MAX;
};

template<>
struct inf<double> {
    static constexpr double value = INT_MAX;
};

template<>
struct inf<std::string> {
    const std::string value = {CHAR_MAX};
};

template<typename T>
struct inf<std::vector<T>> {
static constexpr std::vector<T> value = {inf<T>::value};
};

template<typename T>
struct null;

template<>
struct null<int> {
    static constexpr int value = 0;
};

template<>
struct null<double> {
    static constexpr double value = 0;
};

template<>
struct null<std::string> {
    const std::string value = "";
};

template<typename T>
struct null<std::vector<T>> {
static constexpr std::vector<T> value = {};
};

template<>
struct null<Student> {
    static Student value;
};

Student null<Student>::value = Student("null", 0, 0);

template<>
struct null<std::pair<int, int>> {
    static constexpr std::pair<int, int> value = {0, 0};
};

#endif //BINOMIAL_HEAP_INFNULL_HPP
