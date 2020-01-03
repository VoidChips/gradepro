#ifndef CLASS_H
#define CLASS_H
#include <iostream>
#include <vector>
#include "student.h"

class Class
{
    friend std::ostream &operator<<(std::ostream &, const Class &);
    // course name
    std::string name;
    // course number isn't just a number
    std::string number;
    // capacity is the maxinum number of students
    int section, capacity;
    // students enrolled in the class
    std::vector<Student> students;

public:
    Class() = default;
    Class(std::string, std::string, int, int, std::vector<Student>);
    std::string getName() const;
    std::string getNumber() const;
    int getSection() const;
    int getCapacity() const;
    std::vector<Student> getStudents() const;
    void setName(const std::string);
    void setNumber(const std::string);
    void setSection(const int);
    void setCapacity(const int);
    void setStudents(const std::vector<Student>);
    void addStudent(const Student);
};

#endif // CLASS_H
