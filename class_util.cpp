#include "class_util.h"
void outputClasses(std::ostream &os,
                   const std::vector<Class> &classes)
{
    for (const auto &s : classes)
    {
        os << s << std::endl;
    }
}
void displayClasses(const std::vector<Class> &classes)
{
    int i{1};
    for (const auto &s : classes)
    {
        std::cout << i << ". " << s << std::endl;
        i++;
    }
}