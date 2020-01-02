#include "file_utility.h"

static const std::string tags[] = {"Name", "Number", "Capacity", "Students"};

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

std::vector<std::string> readFile(std::fstream &file)
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
    int score, total;
    double gpa;
    for (const auto line : lines)
    {
        Student temp;
        std::istringstream iss{line};
        // get attributes from line
        while (iss >> f_name >> l_name >> score >> total >> gpa)
        {
            temp.setName(f_name + " " + l_name);
            temp.setGPA(gpa);
            temp.addScore(score, total);
            students.push_back(temp);
        }
    }
    return students;
}

std::vector<Class> processClasses(const std::vector<std::string> lines)
{
    std::vector<Class> classes;
    std::vector<Student> students;
    std::string course, number;
    int section, capacity;
    // this works if the course name doesn't have spaces
    for (size_t i{}; i < lines.size(); i += 4)
    {
        // data for one student consists of 4 lines
        for (size_t j{i}; j < i + 4; ++j)
        {
            // empty students for the next class
            students.clear();
            std::istringstream iss{lines[j]};
            std::string tag;
            char equal;
            iss >> tag >> equal;
            // iss contains data after the tag and = sign now
            // check what tag it was to determine class data type
            if (tag == tags[0] && equal == '=')
            {
                iss >> course;
            }
            if (tag == tags[1] && equal == '=')
            {
                iss >> number >> section;
            }
            if (tag == tags[2] && equal == '=')
            {
                iss >> capacity;
            }
            if (tag == tags[3] && equal == '=')
            {
                // use vector of Students since there may be more than one student
                std::string first, last;
                int score, total;
                double gpa;
                while (iss >> first >> last >>
                       score >> total >> gpa)
                {
                    Student student;
                    student.setName(first + " " + last);
                    student.addScore(score, total);
                    student.setGPA(gpa);
                    students.push_back(student);
                }
            }
        }
        // add the class to the vector
        classes.emplace_back(course, number, section, capacity, students);
    }
    return classes;
}

std::string getRandomStudentName(const std::vector<std::string> names)
{
    int size{static_cast<int>(names.size())};
    // access random element
    return names[rand() % (size - 1)];
}

bool createStudentFile(const std::vector<std::string> names,
                       std::default_random_engine e)
{
    std::ofstream file{"students.txt"};
    if (!file)
    {
        return false;
    }
    std::vector<std::string> written_names;
    std::uniform_real_distribution<double> distribution(0.5, 4.0);
    for (size_t i{}; i < names.size(); ++i)
    {
        std::string name{getRandomStudentName(names)};
        // write name to file if there's no duplicates
        file << std::fixed << std::setprecision(1);
        if (std::find(written_names.begin(), written_names.end(), name) == written_names.end())
        {
            file << std::fixed << std::setprecision(2);
            // random number between 0.5 and 4.0
            file << name << " 0 0 " << distribution(e) << std::endl;
            written_names.push_back(name);
        }
    }
    file.close();
    return true;
}

bool createClassFile(const std::vector<Class> classes)
{
    std::ofstream file{"classes.txt"};
    if (!file)
    {
        return false;
    }
    file << std::fixed << std::setprecision(1);
    for (const auto c : classes)
    {
        // write class data in one line
        file << "Name = " << c.getName() << std::endl;
        file << "Number = " << c.getNumber() << " " << c.getSection() << std::endl;
        file << "Capacity = " << c.getCapacity() << std::endl;
        // have all the students' data written in the same line
        file << "Students =";
        for (const auto s : c.getStudents())
        {
            file << std::fixed << std::setprecision(2);
            /* have the space in front instead of back so that the 
            last student won't end with a space */
            file << " " << s.getName() << " "
                 << s.getGrade().getScore() << " "
                 << s.getGrade().getTotal() << " "
                 << s.getGPA();
        }
        file << "\n\n";
    }
    file.close();
    return true;
}

bool fileExists(const std::string str)
{
    // if the file opens, the file exists
    std::ifstream file{str};
    bool isOpen{file.is_open()};
    file.close();
    return isOpen;
}

// update file to the contents of the vector
void updateStudentFile(const std::vector<Student> students,
                       std::fstream &file)
{
    for (const auto s : students)
    {
        file << std::fixed << std::setprecision(1);
        file << s.getName() << " "
             << s.getGrade().getScore() << " "
             << s.getGrade().getTotal() << " "
             << s.getGPA() << std::endl;
    }
}
