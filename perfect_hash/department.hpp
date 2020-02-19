#ifndef PERFECT_HASH_DEPARTMENT_HPP
#define PERFECT_HASH_DEPARTMENT_HPP

#include <string>
#include <vector>

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
};

#endif //PERFECT_HASH_DEPARTMENT_HPP
