cmake_minimum_required(VERSION 3.15)
project(binomial_heap)

set(CMAKE_CXX_STANDARD 14)

add_executable(binomial_heap main.cpp sqlite3.h sqlite3.c binomial_node.hxx binomial_node.hpp binomial_heap.hxx binomial_heap.hpp infnull.hpp)