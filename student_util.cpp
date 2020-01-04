#include "student_util.h"

void outputStudents(std::ostream &os,
                    const std::vector<Student> &students)
{
    for (const auto &s : students)
    {
        os << s << std::endl;
    }
}

void outputStudents(std::ostream &os,
                    const std::vector<Student> &students,
                    const size_t min, const size_t max)
{
    for (size_t i{min}; i < max; ++i)
    {
        os << students[i] << std::endl;
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

Grade averageGrade(const std::vector<Student> &students)
{
    int score{}, total{};
    // add up all students' score and total
    for (const auto s : students)
    {
        score += s.getGrade().getScore();
        total += s.getGrade().getTotal();
    }
    return Grade{score, total};
}