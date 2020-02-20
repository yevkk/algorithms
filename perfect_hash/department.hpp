#ifndef PERFECT_HASH_DEPARTMENT_HPP
#define PERFECT_HASH_DEPARTMENT_HPP

#include "sqlite3.h"

#include <string>
#include <vector>
#include <iostream>
#include <sstream>

class Student {
private:
    std::string _fullName;
    int _group;
public:
    Student(const std::string &fullName, int group) :
            _fullName(fullName),
            _group(group) {};

    std::string getFullName() {
        return _fullName;
    }

    int getGroup() {
        return _group;
    }
};

std::vector<Student *> getStudentsFromDB(const char *dbFileName) {
    std::vector<Student *> res;
    sqlite3 *db;

    if (sqlite3_open(dbFileName, &db) == SQLITE_OK) {
        sqlite3_stmt *group_stmt;
        sqlite3_prepare(db, "SELECT * from Students;", -1, &group_stmt, nullptr);
        sqlite3_step(group_stmt);

        while (sqlite3_column_text(group_stmt, 0)) {
            std::string name = std::string(reinterpret_cast<const char *>(
                                                   sqlite3_column_text(group_stmt, 1)));


            std::stringstream strGroup;
            strGroup << sqlite3_column_text(group_stmt, 2);

            int group;
            strGroup >> group;

            //std::cout << name << "  " << group << std::endl;

            res.emplace_back(new Student(name, group));
            sqlite3_step(group_stmt);
        }

        sqlite3_finalize(group_stmt);
    } else {
        std::cout << "Failed to open db" << std::endl;
    }

    sqlite3_close(db);
    return res;
}

#endif //PERFECT_HASH_DEPARTMENT_HPP
