#ifndef STUDENT_H
#define STUDENT_H
#include <iostream>
#include <iomanip>
#include "grades.h"

class Student
{
    friend std::ostream &operator<<(std::ostream &, const Student &);
    std::string name;
    // pairs of class name and grade
    ClassGrade grade;
    // cumulative gpa, not the semester or class gpa
    double gpa;

public:
    Student() = default;
    Student(std::string name, ClassGrade grade, double gpa);
    std::string getName() const;
    ClassGrade getGrade() const;
    double getGPA() const;
    void setName(const std::string str);
    void addScore(const int, const int);
    void setGPA(const double x);
    bool operator==(const Student &);
};

#endif // STUDENT_H
