cmake_minimum_required(VERSION 3.15)
project(red_black_tree)

set(CMAKE_CXX_STANDARD 14)

add_executable(red_black_tree main.cpp sqlite3.h sqlite3.c department.hpp rb_node.hpp rb_tree.hpp rb_tree.cpp)