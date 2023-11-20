/*
  rec07_starter.cpp
  Starter Code for required functionality
  Yes, of course, you may add other methods.
  And no, this won't compile. You have to implement the methods and
  fix the cyclic association.

  Temiloluwa Omomuwasan section B
 */

#include <iostream>
#include <string>
#include <vector>
using namespace std;

class Student;

class Course {
    friend ostream& operator<<(ostream& os, const Course& rhs);
public:
    // Course methods needed by Registrar
    Course(const string& courseName);
    const string& getName() const;
    bool addStudent(Student*);
    void removeStudentsFromCourse();

private:
    size_t findStudent1(const Student* name);
    string name;
    vector<Student*> students;
};

class Student {
    friend ostream& operator<<(ostream& os, const Student& rhs);
public:
    // Student methods needed by Registrar
    Student(const string& name);
    const string& getName() const;
    bool addCourse(Course*);

    // Student method needed by Course
    void removedFromCourse(Course*);

private:
    size_t findCourse1(const Course* name);
    string name;
    vector<Course*> courses;
};

class Registrar {
    friend ostream& operator<<(ostream& os, const Registrar& rhs);
public:
    Registrar();
    bool addCourse(const string&);
    bool addStudent(const string&);
    bool enrollStudentInCourse(const string& studentName,
                               const string& courseName);
    bool cancelCourse(const string& courseName);
    void purge();

private:
    size_t findStudent(const string&) const;
    size_t findCourse(const string&) const;

    vector<Course*> courses;
    vector<Student*> students;
};

int main() {

    Registrar registrar;

    cout << "No courses or students added yet\n";
    cout << registrar << endl;
     
    cout << "AddCourse CS101.001\n";
    registrar.addCourse("CS101.001");
    cout << registrar << endl;

    cout << "AddStudent FritzTheCat\n";
    registrar.addStudent("FritzTheCat");
    cout << registrar << endl;

    cout << "AddCourse CS102.001\n";
    registrar.addCourse("CS102.001");
    cout << registrar << endl;

    cout << "EnrollStudentInCourse FritzTheCat CS102.001\n";
    registrar.enrollStudentInCourse("FritzTheCat", "CS102.001");
    cout << "EnrollStudentInCourse FritzTheCat CS101.001\n";
    registrar.enrollStudentInCourse("FritzTheCat", "CS101.001");
    cout << registrar << endl;

    cout << "EnrollStudentInCourse Bullwinkle CS101.001\n";
    cout << "Should fail, i.e. do nothing, "
         << "since Bullwinkle is not a student.\n";
    registrar.enrollStudentInCourse("Bullwinkle", "CS101.001");
    cout << registrar << endl;

    cout << "CancelCourse CS102.001\n";
    registrar.cancelCourse("CS102.001");
    cout << registrar << endl;
   
    /*
    // [OPTIONAL - do later if time]
    cout << "ChangeStudentName FritzTheCat MightyMouse\n";
    registrar.changeStudentName("FritzTheCat", "MightyMouse");
    cout << registrar << endl;  

    cout << "DropStudentFromCourse MightyMouse CS101.001\n";
    registrar.dropStudentFromCourse("MightyMouse", "CS101.001");
    cout << registrar << endl;  

    cout << "RemoveStudent FritzTheCat\n";
    registrar.removeStudent("FritzTheCat");
    cout << registrar << endl;  
    */

    cout << "Purge for start of next semester\n";
    registrar.purge();
    cout << registrar << endl;
} //main

// Course implentation code

Course::Course(const string& courseName) : name(courseName) {}

const string& Course::getName() const { return name; }

bool Course::addStudent(Student* s) {
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
size_t Course::findStudent1(const Student* name) {
    for (size_t i = 0; i < students.size(); ++i) {
        if (name == students[i]) {
            return i;
        }
    }
    return students.size();
}

ostream& operator<<(ostream& os, const Course& rhs) {
    size_t n = 0;
    os  << rhs.getName() << ": ";
    for (const Student* s : rhs.students) {
        ++n;
        cout << s->getName() << "\t";
    }
    if (n == 0) {
        cout << " No Students";
    }
    return os;
}

// Student implementation code

Student::Student(const string& name) : name(name) {}

const string& Student::getName() const { return name; }

bool Student::addCourse(Course* c) {
    if (findCourse1(c) == courses.size()) {
        courses.push_back(c);
        return true;
    }
    return false;
}

// Student method needed by Course
void Student::removedFromCourse(Course* c) {
    size_t idx = findCourse1(c);
    for (size_t i = idx; i < courses.size() - 1; ++i) {
        courses[i] = courses[i+1];
    }
    courses.pop_back();
}

size_t Student::findCourse1(const Course* name) {
    for (size_t i = 0; i < courses.size(); ++i) {
        if (name == courses[i]) {
            return i;
        }
    }
    return courses.size();
}

ostream& operator<<(ostream& os, const Student& rhs) {
    size_t n = 0;
    os << rhs.getName() << ": ";
    for (const Course* c : rhs.courses) {
        ++n;
        cout  << c->getName() << "\t";
    }
    if (n == 0) {
        cout << " No courses";
    }
    return os;
}

// Registrar implementation code

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


  
