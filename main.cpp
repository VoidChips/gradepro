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

void mainMenu(std::vector<Student> &, std::vector<Class> &,
              std::mt19937 &);
void addMenu(std::vector<Student> &, std::vector<Class> &,
             std::mt19937 &);
void viewClassesMenu(const std::vector<Class> &);
int inputIndex(const size_t, const std::string);
bool strIsAlpha(const std::string);
void takeAssignment(std::vector<Student> &, const int, const int, std::mt19937 &);
void displayBorder();
void viewStats(const std::vector<Class> &);
bool strIsNum(const std::string);

int main()
{
    std::random_device device;
    std::mt19937 generator(device());
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
    mainMenu(students, classes, generator);
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

void mainMenu(std::vector<Student> &students, std::vector<Class> &classes,
              std::mt19937 &e)
{
    char c;
    // using std::array for easy loop
    const std::array<std::string, 4> options{
        "A: Add",
        "V: View class",
        "S: View stats",
        "Press e to exit",
    };

    do
    {
        displayBorder();
        std::cout << std::endl;
        // display each option
        for (const auto o : options)
        {
            // format nicely
            std::cout << std::string(30, ' ')
                      << std::setw(20) << std::left
                      << o << std::endl;
        }
        std::cout << "Your choice: ";
        std::cin >> c;
        // handle user choice
        switch (tolower(c))
        {
        case 'a':
            addMenu(students, classes, e);
            break;
        case 'v':
            viewClassesMenu(classes);
            break;
        case 's':
            viewStats(classes);
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

void addMenu(std::vector<Student> &students,
             std::vector<Class> &classes,
             std::mt19937 &e)
{
    const std::array<std::string, 3> options{
        "C: New class",
        "S: New student",
        "A: New assignment"};
    for (const auto o : options)
    {
        std::cout << std::string(30, ' ')
                  << std::setw(20) << std::left
                  << o << std::endl;
    }
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
            // check for class size
            if (classes[c_input].getStudents().size() ==
                classes[c_input].getCapacity())
            {
                std::cout << "Class is full.\n";
            }
            else
            {
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
        }
        break;
    }
    case 'a':
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
            if (classes[c_input].getStudents().empty())
            {
                std::cout << "No students.\n";
            }
            else
            {
                int total;
                std::cout << "Maximum assignment score: ";
                std::cin >> total;
                std::vector<Student> temp{classes[c_input].getStudents()};
                // the copy of students take the assignment
                takeAssignment(temp, 0, total, e); // update students
                classes[c_input].setStudents(temp);
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

/* Assignment can a get a bonus since without a bonus,
there is an equal chance to get any grade, making it much easier to fail the assignment. */
void takeAssignment(std::vector<Student> &students,
                    const int min, const int max,
                    std::mt19937 &e)
{
    std::uniform_int_distribution<int> dist1(min, max);
    std::uniform_int_distribution<int> dist2(0, 1);
    int bonus{rand() %
                  (static_cast<int>(0.50 * max)) +
              (static_cast<int>(0.25 * max))};
    // all students take the assignment
    for (auto &s : students)
    {
        // random performance
        int score{dist1(e)};
        // 50% chance of adding bonus
        // don't add bonus if the sum will be greater than max
        if (dist2(e) == 1 && score + bonus <= max)
        {
            score += bonus;
        }
        s.addScore(score, max);
    }
}

void displayBorder()
{
    std::cout << std::string(80, '-') << std::endl;
}

void viewStats(const std::vector<Class> &classes)
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
            // copy
            std::vector<Student> sample{classes[i].getStudents()};
            // sort the students in descending order
            std::sort(sample.begin(), sample.end(), std::greater<>());
            std::cout << "Students\n\n";
            // display the ordered students
            outputStudents(std::cout, sample);
            std::cout << std::endl;

            std::string s1, s2;
            size_t num1, num2;
            // input check
            do
            {
                // enter the numbers
                std::cout << "Amount of best students: ";
                std::cin >> s1;
                std::cout << "Amount of worst students: ";
                std::cin >> s2;

                std::istringstream iss{s1};
                // read the numbers from strings
                iss >> num1;
                iss.str(std::string()); // clear contents
                iss.clear();
                iss.str(s2);
                iss >> num2;
            } while (!strIsNum(s1) || !strIsNum(s2) || num1 > sample.size() || num2 > sample.size());

            std::cout << "\nBest student(s): \n";
            // display best students
            outputStudents(
                std::cout, sample, 0, num1);

            // sort the students back in ascending order
            std::sort(sample.begin(), sample.end());
            std::cout << "\nWorst student(s): \n";
            // display worst students
            outputStudents(
                std::cout, sample, 0, num2);

            std::cout << "\nClass average: "
                      << averageGrade(sample).getGrade()
                      << std::endl;
        }
    }
}

bool strIsNum(const std::string str)
{
    // not a number if any character is not a number
    for (const auto c : str)
    {
        if (!isdigit(c))
        {
            return false;
        }
    }
    return true;
}