//
// Course cpp file
// Temiloluwa Omomwasan section B

#include "Registrar.h"
#include "Student.h"
#include "Course.h"
using namespace std;

namespace BrooklynPoly {
    Course::Course(const string &courseName) : name(courseName) {}

    const string &Course::getName() const { return name; }

    bool Course::addStudent(Student *s) {
        if (findStudent1(s) == students.size()) {
            students.push_back(s);
            return true;
        }
        return false;
    }

    void Course::removeStudentsFromCourse() {
        for (size_t i = 0; i < students.size() - 1; ++i) {
            students[i]->removedFromCourse(this);
        }
        students.pop_back();
    }

    size_t Course::findStudent1(const Student *name) {
        for (size_t i = 0; i < students.size(); ++i) {
            if (name == students[i]) {
                return i;
            }
        }
        return students.size();
    }

    ostream &operator<<(ostream &os, const Course &rhs) {
        size_t n = 0;
        os << rhs.getName() << ": ";
        for (const Student *s: rhs.students) {
            ++n;
            cout << s->getName() << "\t";
        }
        if (n == 0) {
            cout << " No Students";
        }
        return os;
    }
}