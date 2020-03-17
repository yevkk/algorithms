cmake_minimum_required(VERSION 3.15)
project(optimal_bst)

set(CMAKE_CXX_STANDARD 14)

add_executable(optimal_bst sqlite3.h sqlite3.c main.cpp)