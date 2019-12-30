#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <vector>
#include <utility>
#include <memory>
#include <cctype>
#include <ctime>
#include <random>
#include <limits>
#include <algorithm>
#include "class.h"
#include "file_utility.h"
#include "student_util.h"
#include "class_util.h"

void mainMenu(std::vector<Student> &, std::vector<Class> &);
void addMenu(std::vector<Student> &, std::vector<Class> &);
void viewClassesMenu(const std::vector<Class> &);
int inputIndex(const size_t, const std::string);

int main()
{
    srand(time(0));
    std::ifstream stu_name_file{"student_names.txt"};
    if (!stu_name_file)
    {
        std::cerr << "Error when opening student_names.txt\n";
        return 1;
    }
    // don't need to create students file if it already exists
    if (!fileExists("students.txt"))
    {
        // exit program if the newly created student file doesn't open
        if (!createStudentFile(readFile(stu_name_file)))
        {
            return 1;
        }
    }

    std::ifstream stu_file{"students.txt"};
    if (!stu_file)
    {
        std::cerr << "Error when opening students.txt";
        return 1;
    }
    std::vector<Student> students{processStudents(readFile(stu_file))};
    std::vector<Class> classes;
    stu_name_file.close();
    stu_file.close();
    mainMenu(students, classes);
    return 0;
}

void mainMenu(std::vector<Student> &students, std::vector<Class> &classes)
{
    char c;
    do
    {
        std::cout << "A: Add\nV: View class\nS: View stats\n"
                     "Press e to exit.\n";
        std::cout << "Your choice: ";
        std::cin >> c;
        std::cout << std::endl;
        switch (tolower(c))
        {
        case 'a':
            addMenu(students, classes);
            break;
        case 'v':
            viewClassesMenu(classes);
            break;
        case 's':
            break;
        case 'e':
            std::cout << "Program closing...\n";
            break;
        default:
            std::cout << "Invalid input.\n";
            break;
        }

        std::cout << std::endl;
    } while (tolower(c) != 'e');
}

void addMenu(std::vector<Student> &students, std::vector<Class> &classes)
{
    std::cout << "C: New class\nS: Add a new student to class\n";
    char c;
    std::cout << "Your choice: ";
    std::cin >> c;
    switch (tolower(c))
    {
    case 'c':
    {
        std::string name, number;
        int section, capacity;
        Class temp;
        std::cout << "Class name: ";
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        getline(std::cin, name);
        std::cout << "Course number, section, and capacity "
                     "separated by spaces:\n";
        std::cin >> number >> section >> capacity;
        temp.setName(name);
        temp.setNumber(number);
        temp.setSection(section);
        temp.setCapacity(capacity);
        classes.push_back(temp);
        break;
    }
    case 's':
    {
        if (classes.empty())
        {
            std::cout << "You don't have any classes.\n";
        }
        else
        {
            std::cout << "All classes\n\n";
            displayClasses(classes);
            int c_input{inputIndex(classes.size(), "Pick a class\n")};
            std::cout << "Pick a student to add.\n";
            displayStudents(students);
            int s_input{inputIndex(students.size(), "Pick a student\n")};
            Student temp{students[s_input]};
            classes[c_input].addStudent(temp);
            // find student
            auto it{find(students.begin(), students.end(), temp)};
            // erase a student
            if (it != students.end())
            {
                students.erase(it, it + 1);
            }
        }
        break;
    }
    default:
        std::cerr << "Returning to menu.\n";
        break;
    }
}

void viewClassesMenu(const std::vector<Class> &classes)
{
    if (classes.empty())
    {
        std::cout << "You dont' have any classes.\n";
    }
    else
    {
        std::cout << "All classes\n\n";
        displayClasses(classes);
        int i{inputIndex(classes.size(), "Pick a class\n")};
        if (classes[i].getStudents().empty())
        {
            std::cout << "No students.\n";
        }
        else
        {
            std::cout << "\nAll students\n\n";
            outputStudents(std::cout, classes[i - 1].getStudents());
        }
    }
}

// keep asking for input if it's invalid
int inputIndex(const size_t size, const std::string message)
{
    int i;
    char c;
    do
    {
        std::cout << message << ": ";
        std::cin >> c;
        std::stringstream ss;
        ss << c;
        ss >> i;
        std::cout << i << std::endl;
        // input must be a number
        // input number can't be larger than the size
        // input can't be zero
    } while (!isdigit(c) || i > size || i == 0);
    return i - 1;
}