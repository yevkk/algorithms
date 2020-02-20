cmake_minimum_required(VERSION 3.15)
project(perfect_hash)

set(CMAKE_CXX_STANDARD 14)

add_executable(perfect_hash main.cpp department.hpp sqlite3.h sqlite3.c hash.hpp)