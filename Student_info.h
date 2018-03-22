#ifndef GUARD_student_info_h
#define GUARD_student_info_h

#include <iostream>
#include <vector>
#include <string>

class Core{
public:
    Core() : midterm(0), final(0) { } 
    Core(std::istream& is) : { read(is) } 
    
    std::string name() const { return n; };
    
    virtual std::istream& read(std::istream&);
    virtual double grade() const; 
protected:
    std::istream& read_common(std::istream&);
    double midterm, final;
    std::vector<double> homework;
private:
    std::string n;
};

class Grad: public Core {
public:
    Grad() : thesis(0) { }
    Grad(std::istream& is) { read(is) }

    std::istream read(std::istream&); // inherits virtual-ness from Core::read()
    double grade() const; // inherits virtual-ness from Core::grade()
private:
    double thesis;
};

    /*********************
    * NON MEMBER CLASSES *
    **********************/
bool compare(const Core&, const Core&);
bool compare_grades(const Core&, const Core&);
double grade(double, double, const std::vector<double>&);

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
    // make copy of vector to avoid altering the original vector
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


#endif // GUARD_student_info_h

