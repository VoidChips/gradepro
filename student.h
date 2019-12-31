#ifndef STUDENT_H
#define STUDENT_H
#include <iostream>
#include <map>
#include <iomanip>

class Student
{
    friend std::ostream &operator<<(std::ostream &, const Student &);
    std::string name;
    // pairs of class name and grade
    std::map<std::string, int> grades;
    // cumulative gpa, not the semester or class gpa
    double gpa;

public:
    Student() = default;
    Student(std::string name, std::map<std::string, int> grades, double gpa);
    std::string getName() const;
    std::map<std::string, int> getGrades() const;
    double getGPA() const;
    void setName(const std::string str);
    void setGrades(const std::map<std::string, int> map);
    void setGPA(const double x);
    bool operator==(const Student &);
};

#endif // STUDENT_H
