cmake_minimum_required(VERSION 3.15)
project(splay_tree)

set(CMAKE_CXX_STANDARD 14)

add_executable(splay_tree main.cpp sqlite3.h sqlite3.c splay_tree.hpp splay_tree.hxx)