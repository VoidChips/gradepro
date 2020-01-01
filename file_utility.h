#ifndef FILEUTILITY_H
#define FILEUTILITY_H
#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <sstream>
#include <random>
#include <algorithm>
#include <iomanip>
#include "student.h"
#include "class.h"

std::vector<std::string> readFile(std::ifstream &file);
std::vector<std::string> readFile(std::fstream &file);
std::string getRandomStudentName(const std::vector<std::string>);
bool createStudentFile(const std::vector<std::string>,
                       std::default_random_engine);
bool createClassFile(const std::vector<Class>);
std::vector<Student> processStudents(const std::vector<std::string>);
std::vector<Class> processClasses(const std::vector<std::string>);
bool fileExists(const std::string);
void updateStudentFile(const std::vector<Student>, std::fstream &);
#endif // FILEUTILITY_H
