#include <algorithm> // sort, min
#include <iostream>
#include <cstdio> // EOF
#include <stdexcept> // domain_error
#include <string>

#include "Student_info.h"

    /***************************
    * BASE CORE MEMBER CLASSES *
    ****************************/

std::istream& Core::read_common(std::istream& in){
    in >> n >> midterm >> final;
    return in;
}

std::istream& Core::read(std::istream& in){
    read_common(in);
    read_hw(in, homework);
    return in;
}

double Core::grade() const{
    return ::grade(midterm, final, homework);
}

    /******************************
    * DERIVED GRAD MEMBER CLASSES *
    *******************************/

std::istream& Grad::read(std::istream& in){
    Core::read_common(in);
    in >> thesis;
    read_hw(in, homework);
    return in;
}

double Grad::grade() const{
    // grading policy is the minimum between regular grade and thesis grade
    return std::min(Core::grade(), thesis);
}


    /*************************************
    * HANDLE STUDENT_INFO MEMBER CLASSES *
    **************************************/

Student_info::Student_info(const Student_info& s) : cp(0){
    if (s.cp) cp = s.cp->clone();
}

Student_info& Student_info::operator=(const Student_info& s){
    if (&s != this){
        delete cp;
        if (s.cp)
            cp = s.cp->clone();
        else
            cp = 0;
    }
    return *this;
}

std::istream& Student_info::read(std::istream& in){
    delete cp;

    char ch;
    in >> ch;
    if (ch == 'U') cp = new Core(in);
    else if (ch == 'G') cp = new Grad(in);

    return in;
}

std::string Student_info::letterGrade() const{
    static std::string letterGrades[] = {"A+", "A", "A-", "B+", "B", "B-", "C+", "C", "C-", "D", "F"};
    static int gradeBenchMarks[] =      { 97,   92,  90,   87,   82,  80,   77,   72,  70,   65,  0 };
    static int sizeOfLetterGrades = sizeof(letterGrades) / sizeof(std::string);
    if (cp){
        double finalGrade = cp->grade();
        for (int i = 0; i != sizeOfLetterGrades; ++i)
            if (finalGrade >= gradeBenchMarks[i]) return letterGrades[i];
    } else {
        return "Cannot find letter grade of uninitialized student";
    }

}
    /*********************
    * NON MEMBER CLASSES *
    **********************/

double grade(double midterm, double final, const std::vector<double>& homework){
    if (homework.size() == 0)
        throw std::domain_error("student has done no homework");

    // Use nonmember template function median (defined in Student_info.h) to calculate grade
    double hw_median = 0;
    median(homework.begin(), homework.end(), hw_median);

    return (midterm * 0.2) + (final * 0.4) + (hw_median * 0.4);
}

bool compare(const std::string& s1, const std::string& s2){
    return s1 < s2;
}
