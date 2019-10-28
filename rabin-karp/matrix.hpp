#pragma once

#include <iostream>
#include <cassert>

template <typename T>
class Matrix {
private:

    T **_elements;
public:
    int size;

    Matrix(const int &Size){
        _elements = new char *[Size];
        for (int i = 0; i < Size; i++) {
            _elements[i] = new char[Size];
            for (int j = 0; j < size; j++)
                _elements[i][j] = 0;
        }
        size = Size;
    }

    T operator()(int index_r, int index_c) const {
        assert(index_r < size && "Out of range");
        assert(index_c < size && "Out of range");
        return _elements[index_r][index_c];
    }

    T &operator()(int index_r, int index_c) {
        assert(index_r < size && "Out of range");
        assert(index_c < size && "Out of range");
        return _elements[index_r][index_c];
    }

    T *operator()(int index_r) const {
        assert(index_r < size && "Out of range");
        return _elements[index_r];
    }

    void print() {
        for (int i = 0; i < size; i++) {
            std::cout << i << ") ";
            for (int j = 0; j < size; j++) {
                std::cout << _elements[i][j] << ' ';
            }
            std::cout << std::endl;
        }
    };
};