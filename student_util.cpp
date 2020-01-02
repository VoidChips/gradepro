#include "student_util.h"

void outputStudents(std::ostream &os,
                    const std::vector<Student> &students)
{
    for (const auto &s : students)
    {
        os << s << std::endl;
    }
}

void displayStudents(const std::vector<Student> &students)
{
    int i{1};
    for (const auto &s : students)
    {
        std::cout << i << ". Name: " << s.getName() << " GPA: "
                  << s.getGPA() << std::endl;
        i++;
    }
}