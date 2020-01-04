#include "student.h"

std::ostream &operator<<(std::ostream &os, const Student &student)
{
    os << std::fixed << std::setprecision(2)
       << "Name: " << student.getName()
       << " " << student.getGrade()
       << " GPA: " << student.getGPA();
    return os;
}

Student::Student(std::string name, ClassGrade grade, double gpa)
    : name{name}, grade{grade}, gpa{gpa} {}

std::string Student::getName() const { return name; }
ClassGrade Student::getGrade() const { return grade; }
double Student::getGPA() const { return gpa; }
void Student::setName(const std::string str) { name = str; }
void Student::addScore(const int score, const int total)
{
    grade.setScore(score);
    grade.setTotal(total);
}
void Student::setGPA(const double x) { gpa = x; }
bool Student::operator==(const Student &student)
{
    return name == student.getName() &&
           grade == student.getGrade() &&
           gpa == student.getGPA();
}
bool Student::operator<(const Student &student)
{
    int score1{grade.getScore()}, total1{grade.getTotal()},
        score2{student.getGrade().getScore()},
        total2{student.getGrade().getTotal()};
    // check for division with zero
    if (total1 == 0 || total2 == 0)
    {
        return true;
    }
    // checks for lower score out of total
    return (static_cast<double>(score1) / total1) <
           (static_cast<double>(score2) / total2);
}

bool Student::operator>(const Student &student)
{
    return !((*this) < student);
}