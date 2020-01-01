#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <vector>
#include <utility>
#include <memory>
#include <cctype>
#include <ctime>
#include <limits>
#include <random>
#include <algorithm>
#include "class.h"
#include "file_utility.h"
#include "student_util.h"
#include "class_util.h"

void mainMenu(std::vector<Student> &, std::vector<Class> &);
void addMenu(std::vector<Student> &, std::vector<Class> &);
void viewClassesMenu(const std::vector<Class> &);
int inputIndex(const size_t, const std::string);
bool strIsAlpha(const std::string);

int main()
{
    std::default_random_engine generator;
    std::ifstream stu_name_file{"student_names.txt"};
    // check if the file is open
    if (!stu_name_file)
    {
        std::cerr << "Error when opening student_names.txt\n";
        return 1;
    }
    // don't need to create students file if it already exists
    if (!fileExists("students.txt"))
    {
        // exit program if the newly created student file doesn't open
        if (!createStudentFile(readFile(stu_name_file), generator))
        {
            return 1;
        }
    }

    std::fstream stu_file{"students.txt", std::fstream::in};
    std::vector<Student> students{processStudents(readFile(stu_file))};
    std::vector<Class> classes;
    if (fileExists("classes.txt"))
    {
        std::ifstream class_file{"classes.txt"};
        if (!class_file)
        {
            std::cerr << "Error when opening classes.txt";
        }
        classes = processClasses(readFile(class_file));
        class_file.close();
    }
    stu_name_file.close();
    stu_file.close();
    mainMenu(students, classes);
    // open the file again to clear data, then write
    stu_file.open("students.txt", std::fstream::out);
    updateStudentFile(students, stu_file);

    // create a new file with updated data

    if (!createClassFile(classes))
    {
        std::cerr << "Error when creating classes.txt";
    }
    stu_file.close();
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
            int c_input{inputIndex(classes.size(), "Pick a class")};
            std::cout << "Pick a student to add.\n\n";
            displayStudents(students);
            int s_input{inputIndex(students.size(), "Pick a student")};
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
        std::cout << "You don't have any classes.\n";
    }
    else
    {
        std::cout << "All classes\n\n";
        displayClasses(classes);
        int i{inputIndex(classes.size(), "Pick a class")};
        if (classes[i].getStudents().empty())
        {
            std::cout << "No students.\n";
        }
        else
        {
            std::cout << "\nAll students\n\n";
            outputStudents(std::cout, classes[i].getStudents());
        }
    }
}

// keep asking for input if it's invalid
int inputIndex(const size_t size, const std::string message)
{
    int i;
    // use string instead of char for multiple digit number
    std::string s;
    do
    {
        std::cout << message << ": ";
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cin >> s;
        std::stringstream ss;
        ss << s;
        ss >> i;
        // input must be a number, larger than size, and not zero
    } while (strIsAlpha(s) || i > size || i == 0);
    return i - 1;
}

bool strIsAlpha(const std::string s)
{
    for (const auto c : s)
    {
        if (!isalpha(c))
        {
            return false;
        }
    }
    return true;
}