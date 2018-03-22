#include <algorithm> // sort, min
#include <iostream>
#include <cstdio> // EOF
#include <string>

#include "Student_info.h"

Student_info::Student_info() : midterm(0), final(0), finalGrade(0) { };
Student_info::Student_info(std::istream& is) { read(is); };

std::istream& Core::read_common(istream& in){
    in >> n >> midterm >> final;
    return in;
}

std::istream& Core::read(istream& in){
    read_common(in);
    read_hw(in, homework);
    return in;
}

double Core::grade() const{
    return ::grade(midterm, final, homework);
}

std::istream& Grad::read(istream& in){
    Core::read_common(in);
    in >> thesis;
    read_hw(in, homework);
    return in;
}

double Grad::grade(){
    // grading policy is the minimum between regular grade and thesis grade
    return std::min(Core::grade(), thesis);
}

double ::grade(double midterm, 
               double final, 
               const std::vector<double>& homework){
    double hw_median = 0;
    // definition to nonmember template function median in Student_info.h 
    ::median(homework.begin(), homework.end(), hw_median); 
    return (midterm * 0.2) + (final * 0.4) + (hw_median * 0.4);
}

bool compare(const Compare& c1, const Compare& c2){
    return c1.name() < c2.name();
}

/*
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
}*/