cmake_minimum_required(VERSION 3.15)
project(rabin_karp)

set(CMAKE_CXX_STANDARD 14)

add_executable(rabin_karp main.cpp rabin_karp_extended.hpp matrix.hpp)