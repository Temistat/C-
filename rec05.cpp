/*
  rec05-start.cpp
 */

#include <iostream>
#include <string>
#include <vector>
using namespace std;

class Section {
    class Timeslot {
        friend ostream& operator<<(ostream& os, const Section::Timeslot& rhs);
    public:
        Timeslot(const string& day, int hour) : day(day), hour(hour) {}

    private:
        string day;
        int hour;
    };
    class Studentrecords {
        friend ostream& operator<<(ostream& os, const Section::Studentrecords& rhs);
    public:
        Studentrecords(const string& name) : name(name), grades(14,-1){}

        const string& getName() const{
            return name;
        }
        void setGrade(int week, int grade) {
            grades[week] = grade;
        }

    private:
        string name;
        vector<int> grades;
    };
    friend ostream& operator<<(ostream& os, const Section& rhs);
    friend ostream& operator<<(ostream& os, const Section::Timeslot& rhs);
    friend ostream& operator<<(ostream& os, const Section::Studentrecords& rhs);
public:
    Section(const string& sec, const string& day, int hour) : sec(sec), time(day, hour) {
        if (hour > 12) {
            hour -= 12;
        }
    }

    void addStudent(const string& name) {
        records.push_back(new Studentrecords(name));
    }
    size_t findStudent(const string& name) const{
        for (size_t i = 0; i < records.size(); ++i) {
            if (name == records[i]->getName()) {
                return i;
            }
        }
        return records.size();
    }
    void changeGrade(size_t idx, int grade, int week) {
        records[idx]->setGrade(week, grade);
    }
    // Destructor
    ~Section() {
        cout << "Section " << sec << " is being deleted " << endl;
        for (Studentrecords* s : records) {
            cout << "Deleting" << s->getName() << endl;
            delete s;
        }
    }
    // Copy control
    Section(const Section& rhs) : sec(rhs.sec), time(rhs.time) {
        for (const Studentrecords* s : rhs.records) {
            records.push_back(new Studentrecords(*s));
        }
    }
private:
    string sec;
    Timeslot time;
    vector<Studentrecords*> records;
};

class LabWorker {
    friend ostream& operator<<(ostream& os, const LabWorker& rhs);
public:
    LabWorker(const string& name) : name(name) {}

    void addSection(Section& sec) {
        s = &sec;
    }
    bool haveSec() const {
        if (s != nullptr) {
            return true;
        }
        else{
            return false;
        }
    }
    void addGrade(const string& name, int grade, int week) {
        size_t idx = s->findStudent(name);
        s->changeGrade(idx, grade, week - 1);
    }
private:
    string name;
    Section* s = nullptr;
};

ostream& operator<<(ostream& os, const Section::Timeslot& rhs) {
    os << "[Day: " << rhs.day << ", Start time: ";
    if (rhs.hour > 12) {
        int newHour = rhs.hour - 12;
        os << newHour << "pm],";
    }
    else{
        os << rhs.hour << "am],";
    }
    return os;
}
ostream& operator<<(ostream& os, const Section::Studentrecords& rhs) {
    if (rhs.grades.size() == 0) {
        os << "None";
    }
    else{
        os << "Name: " <<rhs.getName();
        for (int i:rhs.grades) {
            cout << " " << i;
        }
    }
    return os;
}
ostream& operator<<(ostream& os, const Section& rhs) {
    os << "Section: " << rhs.sec << ", Time slot: " << rhs.time << " Students: ";
    if (rhs.records.size() == 0) {
        os << "None";
    }
    else {
        os << endl;
        for (const Section::Studentrecords* r: rhs.records) {
            cout << *r << endl;
        }
     }
    return os;
}
ostream& operator<<(ostream& os, const LabWorker& rhs) {
    if (rhs.haveSec()) {
        os << rhs.name << " has a Section " << *rhs.s << endl;
    }
    else{
        os << rhs.name << " does not has a Section " << endl;
    }
    return os;
}

// Test code
void doNothing(Section sec) { cout << sec << endl; }

int main() {

    cout << "Test 1: Defining a section\n";
    Section secA2("A2", "Tuesday", 16);
    cout << secA2 << endl;

    cout << "\nTest 2: Adding students to a section\n";
     secA2.addStudent("John");
     secA2.addStudent("George");
     secA2.addStudent("Paul");
     secA2.addStudent("Ringo");
    cout << secA2 << endl;

    cout << "\nTest 3: Defining a lab worker.\n";
    LabWorker moe( "Moe" );
    cout << moe << endl;

    cout << "\nTest 4: Adding a section to a lab worker.\n";
    moe.addSection( secA2 );
    cout << moe << endl;

    cout << "\nTest 5: Adding a second section and lab worker.\n";
     LabWorker jane( "Jane" );
     Section secB3( "B3", "Thursday", 11 );
     secB3.addStudent("Thorin");
     secB3.addStudent("Dwalin");
     secB3.addStudent("Balin");
     secB3.addStudent("Kili");
     secB3.addStudent("Fili");
     secB3.addStudent("Dori");
     secB3.addStudent("Nori");
     secB3.addStudent("Ori");
     secB3.addStudent("Oin");
     secB3.addStudent("Gloin");
     secB3.addStudent("Bifur");
     secB3.addStudent("Bofur");
     secB3.addStudent("Bombur");
     jane.addSection( secB3 );
     cout << jane << endl;

    cout << "\nTest 6: Adding some grades for week one\n";
     moe.addGrade("John", 17, 1);
     moe.addGrade("Paul", 19, 1);
     moe.addGrade("George", 16, 1);
     moe.addGrade("Ringo", 7, 1);
     cout << moe << endl;

    cout << "\nTest 7: Adding some grades for week three (skipping week 2)\n";
     moe.addGrade("John", 15, 3);
     moe.addGrade("Paul", 20, 3);
     moe.addGrade("Ringo", 0, 3);
     moe.addGrade("George", 16, 3);
     cout << moe << endl;

    cout << "\nTest 8: We're done (almost)! \nWhat should happen to all "
         << "those students (or rather their records?)\n";

    cout << "\nTest 9: Oh, IF you have covered copy constructors in lecture, "
         << "then make sure the following call works:\n";
    doNothing(secA2);
    cout << "Back from doNothing\n\n";

} //main
