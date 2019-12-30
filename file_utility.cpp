#include "file_utility.h"

std::vector<std::string> readFile(std::ifstream &file)
{
    std::vector<std::string> lines;
    std::string line;
    while (getline(file, line))
    {
        // empty line or line containting comments will be ignored
        if (!line.empty() && line.find('#') == std::string::npos)
        {
            lines.push_back(line);
        }
    }
    return lines;
}

std::vector<Student> processStudents(const std::vector<std::string> lines)
{
    std::vector<Student> students;
    std::string f_name, l_name;
    double gpa;
    for (const auto line : lines)
    {
        Student temp;
        std::istringstream iss{line};
        // get attributes from line
        while (iss >> f_name >> l_name >> gpa)
        {
            temp.setName(f_name + " " + l_name);
            temp.setGPA(gpa);
            students.push_back(temp);
        }
    }
    return students;
}

std::string getRandomStudentName(const std::vector<std::string> names)
{
    int size{static_cast<int>(names.size())};
    // access random element
    return names[rand() % (size - 1)];
}

bool createStudentFile(const std::vector<std::string> names)
{
    std::ofstream file{"students.txt"};
    if (!file)
    {
        std::cerr << "Error when opening student_names.txt" << std::endl;
        return false;
    }
    std::vector<std::string> written_names;
    for (int i{}; i < 10; ++i)
    {
        std::string name{getRandomStudentName(names)};
        // write name to file if there's no duplicates
        if (std::find(written_names.begin(), written_names.end(), name) == written_names.end())
        {
            file << std::fixed << std::setprecision(1);
            file << name << " " << static_cast<double>(rand() % 3 + 1) << std::endl;
            written_names.push_back(name);
        }
    }
    return true;
}

bool fileExists(const std::string str)
{
    std::ifstream file{str};
    return file.is_open();
}
