#ifndef PERFECT_HASH_HASH_HPP
#define PERFECT_HASH_HASH_HPP

#include "department.hpp"
#include <vector>
#include <random>
#include <ctime>

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
        h = (h + b + a * name[i]) % p;
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
        std::cout << tmp.size()  << std::endl << std::endl;

        if (m == 1) {
            elements = tmp;
            tmp.clear();
            return;
        }

        bool flag = false;
        while (!flag) {
            elements.clear();
            elements = std::vector<Student *>(m, nullptr);
            a = rand_int(0, 100);
            b = rand_int(0, 100);

            flag = true;
            for (auto &student: tmp) {
                int index = hashStudent(student->getFullName(), a, b, m, p);
                std::cout << index << std::endl;
                if (elements[index] != nullptr) {
                    flag = false;
                    break;
                }
                elements[index] = student;
            }
        }


    }

//    Student *getStudent(const std::string &str, int p) {
//        return elements[hashFunction(hashString(str, p), a, b, m, p)];
//    }
};

class HashTable {
public:
    std::vector<HashNode> data;
    int p;
    int m;
    int a;
    int b;

    HashTable(std::vector<Student *> elements) {
        p = 101;
        m = 37;
        data = std::vector<HashNode>(m);

        a = rand_int(1, 100);
        b = rand_int(0, 100);

        for (auto &e:elements) {
            data[hashStudent(e->getFullName(), a, b, m, p)].tmp.push_back(e);
        }

        for (auto &node:data) {
            node.fill(p);
        }
    }

//    Student *getStudent(const std::string &str) {
//        return data[hashFunction(hashString(str, p), a, b, m, p)].getStudent(str, p);
//    }
};


#endif //PERFECT_HASH_HASH_HPP
