cmake_minimum_required(VERSION 3.15)
project(b_plus_tree)

set(CMAKE_CXX_STANDARD 14)

add_executable(b_plus_tree main.cpp bplus_tree.hpp bplus-tree.hxx)