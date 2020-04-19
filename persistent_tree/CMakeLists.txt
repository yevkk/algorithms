cmake_minimum_required(VERSION 3.15)
project(persistent_tree)

set(CMAKE_CXX_STANDARD 14)

add_executable(persistent_tree main.cpp sqlite3.h sqlite3.c department.hpp persistent_tree.hpp persistent_tree.cpp)