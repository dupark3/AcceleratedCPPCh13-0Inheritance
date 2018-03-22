#ifndef GUARD_student_info_h
#define GUARD_student_info_h

#include <iostream>
#include <vector>
#include <string>

class Student_info{
public:
    Student_info(); // default constructor
    Student_info(std::istream&); // constructor with argument
    std::istream& read(std::istream&);
    std::string name() const { return n; }; // accessor
    std::string letterGrade() const; // accessor

private:
    std::string n;
    double midterm;
    double final;
    std::vector<double> homework;
    // double homework[];
    double finalGrade;
};

template <class container>
std::istream& read_hw(std::istream& is, container& c){
    if (is){
        c.clear();
        double x;
        while (is >> x)
            c.push_back(x);
        is.clear();
    }
    return is;
};

template <class inputIter, class T>
void median(inputIter first, inputIter last, T& init){
    // in order to find the median, we need to sort, but we don't want to change the container itself, so we copy the elements and then sort
    std::vector<T> temp;
    while(first != last){
        temp.push_back(*first);
        ++first;
    }
    std::sort(temp.begin(), temp.end());

    // if even numbered, find the average of the middle two. If odd numbered, the median is the middle element.
    size_t size = temp.size();
    size_t mid = size / 2;
    size % 2 == 0 ? init = (temp[mid - 1] + temp[mid]) / 2 : init = temp[mid];
};

bool compare(const Student_info&, const Student_info&);

#endif // GUARD_student_info_h

