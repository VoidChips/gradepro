#ifndef STUDENT_UTIL_H
#define STUDENT_UTIL_H
#include <iostream>
#include <vector>
#include "student.h"

// useful for printing or writing
void outputStudents(std::ostream &os,
                    const std::vector<Student> &students);
// output in range
void outputStudents(std::ostream &os,
                    const std::vector<Student> &students,
                    const size_t min, const size_t max);
void displayStudents(const std::vector<Student> &students);
Grade averageGrade(const std::vector<Student> &students);
#endif
