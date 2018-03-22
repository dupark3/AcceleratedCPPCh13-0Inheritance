#include <algorithm> // sort, min
#include <iostream>
#include <cstdio> // EOF
#include <stdexcept> // domain_error
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

    /*********************
    * NON MEMBER CLASSES *
    **********************/

double ::grade(double midterm, double final, const std::vector<double>& homework){
    if (homework.size() == 0)
        throw std::domain_error("student has done no homework");
    
    // Use nonmember template function median (defined in Student_info.h) to calculate grade
    double hw_median = 0;
    median(homework.begin(), homework.end(), hw_median); 

    return (midterm * 0.2) + (final * 0.4) + (hw_median * 0.4);
}

bool compare(const Core& c1, const Core& c2){
    return c1.name() < c2.name();
}

bool compare_grades(const Core& c1, const Core& c2){
    // grade function is virtual, so compiler will decide if a Core object or Grad reference has been passed 
    // and call the appropriate grade() function
    return c1.grade() < c2.grade(); 
}