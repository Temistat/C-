//
// Student cpp file
//Temiloluwa Omomwasan section B
#include "Registrar.h"
#include "Student.h"
#include "Course.h"
using namespace std;

namespace BrooklynPoly {
    Student::Student(const string &name) : name(name) {}

    const string &Student::getName() const { return name; }

    bool Student::addCourse(Course *c) {
        if (findCourse1(c) == courses.size()) {
            courses.push_back(c);
            return true;
        }
        return false;
    }

// Student method needed by Course
    void Student::removedFromCourse(Course *c) {
        size_t idx = findCourse1(c);
        for (size_t i = idx; i < courses.size() - 1; ++i) {
            courses[i] = courses[i + 1];
        }
        courses.pop_back();
    }

    size_t Student::findCourse1(const Course *name) {
        for (size_t i = 0; i < courses.size(); ++i) {
            if (name == courses[i]) {
                return i;
            }
        }
        return courses.size();
    }

    ostream &operator<<(ostream &os, const Student &rhs) {
        size_t n = 0;
        os << rhs.getName() << ": ";
        for (const Course *c: rhs.courses) {
            ++n;
            cout << c->getName() << "\t";
        }
        if (n == 0) {
            cout << " No courses";
        }
        return os;
    }
}