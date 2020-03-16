#ifndef  RED_BLACK_TREE_DEPARTMENT_HPP
#define  RED_BLACK_TREE_DEPARTMENT_HPP

#include "sqlite3.h"

#include <string>
#include <vector>
#include <iostream>
#include <sstream>
#include <cassert>

class Student {
private:
    std::string _fullName;
    int _group;
    double _averagePoint;
public:
    Student(const std::string &fullName, int group, double averagePoint) :
            _fullName(fullName),
            _group(group),
            _averagePoint(averagePoint) {};

    std::string getFullName() {
        return _fullName;
    }

    int getGroup() {
        return _group;
    }

    double getAveragePoint() {
        return _averagePoint;
    }

    void decAveragePoint(double newValue) {
        assert((newValue >= 0) && "newValue < 0");
        assert((newValue <= _averagePoint) && "new value bigger than current value");
        _averagePoint = newValue;
    }
};

inline std::vector<Student *> getStudentsFromDB(const char *dbFileName) {
    std::vector<Student *> res;
    sqlite3 *db;

    if (sqlite3_open(dbFileName, &db) == SQLITE_OK) {
        sqlite3_stmt *stmt;
        sqlite3_prepare(db, "SELECT * from Students;", -1, &stmt, nullptr);
        sqlite3_step(stmt);

        while (sqlite3_column_text(stmt, 0)) {
            std::string name = std::string(reinterpret_cast<const char *>(
                                                   sqlite3_column_text(stmt, 1)));

            std::stringstream strGroup;
            strGroup << sqlite3_column_text(stmt, 2);
            int group;
            strGroup >> group;

            std::stringstream strAvPoint;
            strAvPoint << sqlite3_column_text(stmt, 3);
            double avPoint;
            strAvPoint >> avPoint;

            res.emplace_back(new Student(name, group, avPoint));
            sqlite3_step(stmt);
        }

        sqlite3_finalize(stmt);
    } else {
        std::cout << "Failed to open db" << std::endl;
    }

    sqlite3_close(db);
    return res;
}

inline std::ostream& operator<<(std::ostream &os, Student &student) {
    os << student.getFullName() << ",  AvPoint:" << student.getAveragePoint();
    return os;
}

inline bool operator<(Student &studentL, Student &studentR) {
    return studentL.getAveragePoint() < studentR.getAveragePoint();
}

inline bool operator>(Student &studentL, Student &studentR) {
    return studentL.getAveragePoint() > studentR.getAveragePoint();
}

inline bool operator==(Student &studentL, Student &studentR) {
    return (!(studentL < studentR)) && (!(studentL > studentR));
}

inline bool operator>=(Student &studentL, Student &studentR) {
    return !(studentL < studentR);
}

inline bool operator<=(Student &studentL, Student &studentR) {
    return !(studentL > studentR);
}

#endif // RED_BLACK_TREE_DEPARTMENT_HPP
