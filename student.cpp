#include "student.h"

std::ostream &operator<<(std::ostream &os, const Student &student)
{
    os << std::fixed << std::setprecision(2)
       << "Name: " << student.getName() << " GPA: " << student.getGPA();
    return os;
}

Student::Student(std::string name, std::map<std::string, int> grades, double gpa)
    : name{name}, grades{grades}, gpa{gpa} {}

std::string Student::getName() const { return name; }
std::map<std::string, int> Student::getGrades() const { return grades; }
double Student::getGPA() const { return gpa; }
void Student::setName(const std::string str) { name = str; }
void Student::setGrades(const std::map<std::string, int> map) { grades = map; }
void Student::setGPA(const double x) { gpa = x; }
bool Student::operator==(const Student &student)
{
    return name == student.getName() &&
           grades == student.getGrades() &&
           gpa == student.getGPA();
}
