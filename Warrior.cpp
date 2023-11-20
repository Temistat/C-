//
// Temiloluwa Omomuwasan too2007 section B
//
#include "Noble.h"
#include "Warrior.h"
#include <iostream>
using namespace std;

namespace WarriorCraft {
    Warrior::Warrior(const string& name, int num) : name(name), num(num), ishired(false){}

    void Warrior::employed(Noble* n) {
        noble = n;
        ishired = true;
    }

    void Warrior::unemployed() {
        noble = nullptr;
        ishired = false;
    }

    bool Warrior::isHired() const {
        return ishired;
    }

    int Warrior::getnum() const{
        return num;
    }

    const string Warrior::getname() const{
        return name;
    }

    void Warrior::makezero() {
        num = 0;
    }
    void Warrior::changestrength(double num1, double num2) {
        double num3 = 1 - (num1/num2);
        num *= num3;
    }
    bool Warrior::runaway() {
        if (isHired()) {
            cout << name << " flees in terror, abandoning his lord, " << noble->getname() << endl;
            noble->runaway(*this);
            unemployed();
            return true;
        }
        return false;
    }
    ostream& operator<<(ostream& os, const Warrior& rhs) {
        os << "    " << rhs.name << ": " << rhs.num << endl;
        return os;
    }
}
