/*
Exercise 13-0
Compile, execute, and test the programs in this chapter.

*/

#include <algorithm> // sort, max
#include <cstddef> // size_t
#include <iomanip> // streamsize
#include <iostream>
#include <stdexcept> // domain_error
#include <string>
#include <vector>

#include "Student_info.h"

typedef std::vector<Core*>::size_type vec_size;
typedef std::string::size_type string_size;

int main() {
    std::cout << "Enter each student's status (U, G, or P), name, midterm grade, final grade, and homework grades: " << std::endl;

    // object of the handle class, dynamically allocates, deallocates, and calls virtual functions
    std::vector<Student_info> students;
    Student_info record;
    string_size maxLen = 0;

    // call handle's read function, which allocates appropriate object
    while(record.read(std::cin)){
        maxLen = std::max(maxLen, record.name().size());
        students.push_back(record);
    }

    // sort
    std::sort(students.begin(), students.end(), Student_info::compare);

    // output
    for (vec_size i = 0; i != students.size(); ++i){
        std::cout << students[i].name()
                  << std::string(maxLen + 1 - students[i].name().size(), ' ');
        if (students[i].checkRequirementsMet()){
            double final_grade = students[i].grade(); // calls handle's grade which virtually calls appropriate grade()
            std::streamsize prec = std::cout.precision();
            std::cout << std::setprecision(3) << final_grade
                      << std::setprecision(prec) << "  "
                      << students[i].letterGrade() << std::endl;
        } else {
            std::cout << "Student did not meet the requirements" << std::endl;
        }
    }
    return 0;
}
