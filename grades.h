#ifndef GRADES_H
#define GRADES_H
#include <iostream>
#include <vector>

// Grade could be any grade, like a grade for a test
class Grade
{
    friend std::ostream &operator<<(std::ostream &,
                                    const Grade &);
    int score, total;

public:
    Grade();
    Grade(int, int);
    virtual ~Grade() = default;
    int getScore() const;
    int getTotal() const;
    char getGrade() const;
    virtual void setScore(const int);
    virtual void setTotal(const int);
    bool operator==(const Grade &);
};

class ClassGrade : public Grade
{
    friend std::ostream &operator<<(std::ostream &,
                                    const ClassGrade &);
public:
    ClassGrade() = default;
    virtual ~ClassGrade() = default;
    virtual void setScore(const int);
    virtual void setTotal(const int);
};

#endif