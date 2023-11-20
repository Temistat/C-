//
// Registrar cpp file
// Temiloluwa Omomwasan section B

#include "Registrar.h"
#include "Student.h"
#include "Course.h"
using namespace std;

namespace BrooklynPoly {
    Registrar::Registrar() {};
    bool Registrar::addCourse(const string& c) {
        if (findCourse(c) == courses.size()) {
            courses.push_back(new Course(c));
            return true;
        }
        return false;
    }
    bool Registrar::addStudent(const string& s) {
        if (findCourse(s) == courses.size()) {
            students.push_back(new Student(s));
            return true;
        }
        return false;
    }

    bool Registrar::enrollStudentInCourse(const string& studentName, const string& courseName) {
        size_t idx1 = findStudent(studentName);
        size_t idx2 = findCourse(courseName);
        if (idx1 != students.size() && idx2 != courses.size()) {
            return students[idx1]->addCourse(courses[idx2]) &&
                   courses[idx2]->addStudent(students[idx1]);
        }
        return false;
    }

    bool Registrar::cancelCourse(const string& courseName) {
        size_t idx = findCourse(courseName);
        if (idx != courses.size()) {
            for (Student* s : students) {
                s->removedFromCourse(courses[idx]);
            }
            delete courses[idx];
            for (size_t i = idx; i < courses.size() - 1; ++i) {
                courses[i] = courses[i+1];
            }
            courses.pop_back();
            return true;
        }
        return false;
    }

    void Registrar::purge() {
        for (Course* c : courses) {
            delete c;
        }
        courses.clear();
        for (Student* s : students) {
            delete s;
        }
        students.clear();
    }

    size_t Registrar::findStudent(const string& name) const {
        for (size_t i = 0; i < students.size(); ++i) {
            if (name == students[i]->getName()) {
                return i;
            }
        }
        return students.size();
    }
    size_t Registrar::findCourse(const string& name) const {
        for (size_t i = 0; i < courses.size(); ++i) {
            if (name == courses[i]->getName()) {
                return i;
            }
        }
        return courses.size();
    }
    ostream& operator<<(ostream& os, const Registrar& rhs) {
        os << "Registrar's Report\n";
        if  (rhs.courses.size() == 0) {
            cout << "Course: " << endl;
        }
        else {
            cout << "Courses:\n";
            for (const Course* c : rhs.courses) {
                cout << *c << endl;
            }
        }
        if  (rhs.students.size() == 0) {
            cout << "Student: " <<endl;
        }
        else {
            cout << "Students:\n";
            for (const Student* s : rhs.students) {
                cout << *s << endl;
            }
        }
        return os;
    }
}


