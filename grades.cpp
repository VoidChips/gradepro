#include <string>
#include <sstream>
#include "grades.h"

std::ostream &operator<<(std::ostream &os, Grade &grade)
{
    os << "Grade: " << grade.getScore() << " / " << grade.getTotal() << " = " << grade.getGrade();
    return os;
}

Grade::Grade() : score{0}, total{0} {}
Grade::Grade(int x, int y) : score{x}, total{y} {}
int Grade::getScore() const { return score; }
int Grade::getTotal() const { return total; }

char Grade::getGrade() const
{
    // there is no grade if total is zero
    if (!total)
    {
        return 'N';
    }
    double grade{static_cast<double>(score) / total};
    grade *= 100; // move up 2 digits
    std::string s;
    std::stringstream ss;
    ss << grade;
    ss >> s; // string form of the number

    if (grade == 100.0)
    {
        return 'A';
    }
    else if (s.length() >= 2)
    {
        // if the first digit is 9, then the grade was atleast 90%
        switch (s[0])
        {
        case '6':
            return 'D';
            break;
        case '7':
            return 'C';
            break;
        case '8':
            return 'B';
            break;
        case '9':
            return 'A';
            break;
        default:
            // if the grade wasn't A, B, C, or D, then the student failed
            return 'F';
            break;
        }
    }
    // if the grade is a single digit, obviously it's less than 60%
    else
    {
        return 'F';
    }
}

void Grade::setScore(const int x) { score = x; }
void Grade::setTotal(const int x) { total = x; }
bool Grade::operator==(const Grade &grade)
{
    return score == grade.getScore() &&
           total == grade.getTotal();
}

std::ostream &operator<<(std::ostream &os,
                         const ClassGrade &grade)
{
    os << "Grade: " << grade.getScore() << " / " << grade.getTotal() << " = " << grade.getGrade();
    return os;
}

void ClassGrade::setScore(const int x)
{
    Grade::setScore(getScore() + x);
}
void ClassGrade::setTotal(const int x)
{
    Grade::setTotal(getTotal() + x);
}
