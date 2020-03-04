cmake_minimum_required(VERSION 3.15)
project(binomial_heap)

set(CMAKE_CXX_STANDARD 14)

add_executable(binomial_heap main.cpp binominal_node.cpp binominal_node.hpp binomial_heap.cpp binomial_heap.hpp)