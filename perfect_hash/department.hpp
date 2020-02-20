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
    int _mark;
public:
    Student(const std::string &fullName, int mark) :
            _fullName(fullName),
            _mark(mark) {};

    std::string getFullName() {
        return _fullName;
    }

    int getMark() {
        return _mark;
    }
};

class Group {
private:
    std::string _name;
    std::vector<Student *> _students;
public:
    Group(const std::string &name, const std::vector<Student *> &students) :
            _name(name),
            _students(students) {};

    explicit Group(const std::string &name) :
            _name(name),
            _students() {};

    std::string getName() {
        return _name;
    };

    std::vector<Student *> getStudents() {
        return _students;
    };

    void addStudent(const std::string &fullName, int mark) {
        _students.push_back(new Student(fullName, mark));
    }

    void addStudent(Student *student) {
        _students.push_back(student);
    }
};

class Department {
public:
    std::vector<Group *> groups;

    explicit Department(const std::vector<Group *> groupsArg) :
            groups(groupsArg) {};

    explicit Department(const char *dbFilename) {
        sqlite3 *db;
        sqlite3_stmt *stmt;

        if (sqlite3_open("../../department.db", &db) == SQLITE_OK) {
            sqlite3_prepare(db, "SELECT * from Groups;", -1, &stmt, nullptr);//preparing the statement
            sqlite3_step(stmt);
            while (sqlite3_column_text(stmt, 0)) {
                std::stringstream strValueID;
                strValueID << sqlite3_column_text(stmt, 0);

                int intValueID;
                strValueID >> intValueID;

                int id = intValueID;

                std::string name = std::string(reinterpret_cast<const char *>(
                                                       sqlite3_column_text(stmt, 1)
                                               ));

                std::cout << name << std::endl;
                sqlite3_step(stmt);
            }
        } else {
            std::cout << "boooo";
        }
    }
};

#endif //PERFECT_HASH_DEPARTMENT_HPP
