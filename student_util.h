#ifndef STUDENT_UTIL_H
#define STUDENT_UTIL_H
#include <iostream>
#include <vector>
#include "student.h"

// useful for printing or writing
void outputStudents(std::ostream &os,
                    const std::vector<Student> &students);
void displayStudents(const std::vector<Student> &students);                    
#endif
