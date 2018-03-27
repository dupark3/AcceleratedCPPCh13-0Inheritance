#ifndef GUARD_student_info_h
#define GUARD_student_info_h

#include <stdexcept> // runtime_error
#include <iostream>
#include <vector>
#include <string>

// handle class
class Student_info{
public:
    Student_info() : cp(0) { }
    Student_info(std::istream& is) : cp(0) { read(is) }
    Student_info(const Student_info&);
    Student_info& operator= (const Student_info&);
    ~Student_info() { delete cp; }

    std::istream& read(std::istream&);
    std::string name() const{
        if(cp) return cp->name();
        else throw std::runtime_error("Cannot find name of uninitialized student");
    }
    double grade() const{
        if(cp) return cp->grade();
        else throw std::runtime_error("Cannot find grade of uninitialized student");
    }
    static bool compare(const Student_info& s1, const Student_info& s2){
        return compare(s1.name(), s2.name());
    }

private:
    Core* cp;
};

class Core{
friend class Student_info;
public:
    Core() : midterm(0), final(0) { }
    Core(std::istream& is) { read(is); }

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
    Grad(std::istream& is) { read(is); }

    std::istream& read(std::istream&); // inherits virtual-ness from Core::read()
    double grade() const; // inherits virtual-ness from Core::grade()
private:
    double thesis;
};

    /*********************
    * NON MEMBER CLASSES *
    **********************/
bool compare(const Core&, const Core&);
bool compare_Core_pointers(const Core*, const Core*);
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

