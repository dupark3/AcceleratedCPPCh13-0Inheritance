#include <algorithm> // sort
#include <iostream>
#include <cstdio> // EOF
#include <string>

#include "Student_info.h"

Student_info::Student_info() : midterm(0), final(0), finalGrade(0) { };
Student_info::Student_info(std::istream& is) { read(is); };

std::istream& Student_info::read(std::istream& in) {
    in >> n >> midterm >> final;
    ::read_hw(in, homework);
    double hw_median = 0;
    ::median(homework.begin(), homework.end(), hw_median);
    finalGrade = (midterm * 0.2) + (final * 0.4) + (hw_median * 0.4);

    return in;
}

std::string Student_info::letterGrade() const{
    // static const variables of letter grade benchmarks, corresponding letter grades, and number of grades
    static const double  numbers[] = {97, 94, 90, 87, 84, 80, 77, 74, 70, 60, 0};
    static const char* const letters[] = {"A+", "A", "A-", "B+", "B", "B-", "C+", "C", "C-", "D", "F"};
    static const size_t numberSize = sizeof(numbers) / sizeof(*numbers);

    for (size_t i = 0; i != numberSize; ++i){
        if (finalGrade >= numbers[i]){
            return letters[i];
        }
    }

    return "?\?\?";
}

bool compare(const Student_info& x, const Student_info& y){
    return x.name() < y.name();
}



