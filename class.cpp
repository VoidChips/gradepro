#include "class.h"

std::ostream &operator<<(std::ostream &os, const Class &course)
{
    os << "Course name: " << course.getName() << " " << course.getNumber()
       << '-' << course.getSection() << " Size: " << course.getStudents().size()
       << '/' << course.getCapacity();
    return os;
}

Class::Class(std::string name, std::string num, int sect, int cap, std::vector<Student> students)
    : name{name}, number{num}, section{sect}, capacity{cap}, students{students} {}

std::string Class::getName() const { return name; }
std::string Class::getNumber() const { return number; }
int Class::getSection() const { return section; }
int Class::getCapacity() const { return capacity; }
std::vector<Student> Class::getStudents() const { return students; }

void Class::setName(const std::string str) { name = str; }
void Class::setNumber(const std::string num) { number = num; }
void Class::setSection(const int num) { section = num; }
void Class::setCapacity(const int num) { capacity = num; }
void Class::setStudents(const std::vector<Student> vec) { students = vec; }
void Class::addStudent(const Student student) { students.push_back(student); }
