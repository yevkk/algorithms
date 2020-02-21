#include "department.hpp"
#include "hash.hpp"
#include <iostream>

int main() {
    auto elements = getStudentsFromDB("../../department.db");
    HashTable hash(elements);

    return 0;
}
