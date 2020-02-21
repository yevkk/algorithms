#ifndef PERFECT_HASH_HASH_HPP
#define PERFECT_HASH_HASH_HPP

#include "department.hpp"
#include <vector>
#include <random>
#include <ctime>
#include <conio.h>

int rand_int(int min, int max) {
    static std::random_device rd;
    static std::seed_seq seed{rd(), static_cast<unsigned int>(time(nullptr))};
    static std::mt19937_64 gen(seed);
    std::uniform_int_distribution<int> dist(min, max);

    return dist(gen);
}

int hashString(const std::string &str, int p) {
    int h = 0;
    for (int i = 0; i < str.size(); i++) {
        h = (h + (int) str.size() * str[i]) % p;
    }
    return h;
}

int hashStudent(std::string name, int a, int b, int m, int p) {
    int h = 0;
    for (int i = 0; i < name.size(); i++) {
        h = (b + a * (h + (int) name[i])) % p;
        std::cout << h << " (" << (int) name[i] << ")  ";
    }
    return h % m;
}

class HashNode {
public:
    int a;
    int b;
    int m;
    std::vector<Student *> tmp;
    std::vector<Student *> elements;

    HashNode() {
        a = b = m = 0;
        tmp = std::vector<Student *>();
    }

    void fill(int p) {
        m = (int) (tmp.size() * tmp.size());
        std::cout << "MJ: " << tmp.size() << std::endl << std::endl;

        if (m == 1) {
            elements = tmp;
            tmp.clear();
            return;
        }

        bool flag = false;
        while (!flag) {
            elements.clear();
            elements = std::vector<Student *>(m, nullptr);
            a = rand_int(1, p - 1);
            b = rand_int(0, p - 1);

            flag = true;
            for (auto &student: tmp) {
                int index = hashStudent(student->getFullName(), a, b, m, p);
                std::cout << index << std::endl;
                if (elements[index] != nullptr) {
//                    std::cout << "ERROR::" << index << "  " << student->getFullName() << "  "
//                              << elements[index]->getFullName() << "  " << a << "  " << b << std::endl;
                    flag = false;
                    break;
                }
                elements[index] = student;
            }
        }


    }

    Student *getStudent(const std::string &str, int p) {
        return elements[hashStudent(str, a, b, m, p)];
    }
};

class HashTable {
public:

    std::vector<HashNode> data;
    int p;
    int m;
    int a;
    int b;

    HashTable(std::vector<Student *> elements) {
        p = 2153;
        m = 50;
        data = std::vector<HashNode>(m);

        a = rand_int(1, p - 1);
        b = rand_int(0, p - 1);

        for (auto &e:elements) {
            data[hashStudent(e->getFullName(), a, b, m, p)].tmp.push_back(e);
        }

        for (auto &node:data) {
            node.fill(p);
        }
    }

    Student *getStudent(const std::string &str) {
        return data[hashStudent(str, a, b, m, p)].getStudent(str, p);
    }
};


#endif //PERFECT_HASH_HASH_HPP
