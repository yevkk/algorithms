cmake_minimum_required(VERSION 3.15)
project(fibonacci_heap)

set(CMAKE_CXX_STANDARD 14)

add_executable(fibonacci_heap main.cpp sqlite3.h sqlite3.c fibonacci_heap.hpp fibonacci_heap.hxx)