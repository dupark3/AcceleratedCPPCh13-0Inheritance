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
    std::cout << "Enter each student's status (U or G), name, midterm grade, final grade, and homework grades: " << std::endl;

    std::vector<Core*> students;
    Core* record;
    string_size maxLen = 0;
    char ch;

    // read and store the data
    while(std::cin >> ch){
        if (ch == 'U')
            record = new Core;
        else if (ch == 'G')
            record = new Grad;
        record->read(std::cin); // virtual call to read
        maxLen = std::max(maxLen, record->name().size());
        students.push_back(record);
    }

    // sort
    std::sort(students.begin(), students.end(), compare_Core_pointers);

    // output
    for (vec_size i = 0; i != students.size(); ++i){
        std::cout << students[i]->name()
                  << std::string(maxLen + 1 - students[i]->name().size(), ' ');
        try {
            double final_grade = students[i]->grade(); // Core::grade
            std::streamsize prec = std::cout.precision();
            std::cout << std::setprecision(3) << final_grade
                 << std::setprecision(prec) << std::endl;
        } catch (std::domain_error e) {
            std::cout << e.what() << std::endl;
        }
        delete students[i];
    }
    return 0;
}
