cmake_minimum_required(VERSION 3.15)
project(strassen_algorithm)

set(CMAKE_CXX_STANDARD 14)

add_executable(strassen_algorithm main.cpp matrix.cpp matrix.hpp)

#set(CMAKE_BUILD_TYPE Release)
#target_compile_options(strassen_algorithm PRIVATE -O3)