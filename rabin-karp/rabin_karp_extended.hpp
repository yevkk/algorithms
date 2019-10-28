#pragma once

#include "matrix.hpp"

int hash(char num);

template <typename T>

int rabin_karp_extended(Matrix<T> M, Matrix<T> P);

#include "rabin_karp_extended.hxx"