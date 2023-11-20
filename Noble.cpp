//
// Created by Admin on 4/13/2023.
// Temiloluwa Omomuwasan section b homework 7 too2007

#include "Noble.h"
#include "Protector.h"
#include <iostream>
#include <string>
#include  <vector>
using namespace std;

namespace Warriorcraft {
    Noble::Noble(const string& name, double strength) : name(name), strength(strength), isAlive(true) {
    }
    void Noble::makezero() {}; // to make all the warrior strength zero when they lose a battle.
    double Noble::getsum() const { return 0; }; //gets the sum of the all warriors.
    void Noble::changestrength(double num1, double num2) {};
    void Noble::display(ostream& os) const {};
    void Noble::battling() {};
    void Noble::defend() {};
    void Noble::battle(Noble& n) {
        cout << name << " battles " << n.name << endl;
        double num1 = getsum();
        double num2 = n.getsum();
        if (isAlive && n.isAlive) {
            if (num1 == 0 && num2 == 0) {
                cout << "They bout do not have armies, they cant do shit" << endl;
            } // checks if both nobles are dead and gives adequate response.
            else if (num1 != 0 && num2 != 0) {
                if (num2 == num1) {
                    makezero();
                    n.makezero();
                    isAlive = false;
                    n.isAlive = false;
                    cout << "Mutual Annihilation: " << name << " and " << n.name << "die at each other's hands" << endl;
                } // checks if the strength are equal to each other and gives adequate response.
                else if (num2 > num1) {
                    makezero();
                    n.changestrength(num1,num2);
                    battling();
                    n.battling();
                    isAlive = false;
                    cout << "Ugh!\n" << n.name << " defeats " << name << endl;
                } // checks whose strength is more and does what the homework says.
                else if (num1 > num2 ) {
                    n.makezero();
                    changestrength(num2,num1);
                    battling();
                    n.battling();
                    n.isAlive = false;
                    cout << "Ugh!\n" << name << " defeats " << n.name << endl;
                }// checks whose strength is more and does what the homework says.
            }
            else if (num1 == 0 || num2 == 0) {
                if (num1 == 0) {
                    n.battling();
                    isAlive = false;
                    cout << "Ugh!\n" << n.name << " defeats " << name << endl;
                }
                else if (num2 == 0) {
                    battling();
                    n.isAlive = false;
                    cout << "Ugh!\n" << name << " defeats " << n.name << endl;
                }
            }// checks if one person is dead and does not battle and then gives adequate response.
        }
        else if(isAlive || n.isAlive) {
            if (isAlive) {
                battling();
                cout << "He's dead, " << name << endl;
            }
            else if(n.isAlive) {
                n.battling();
                cout << "He's dead, " << n.name << endl;
            }
        }
        else if(!isAlive && !n.isAlive) {
            cout << "Oh, NO!  They're both dead!  Yuck!" << endl;
        }

    }
//Lord class
    Lord::Lord(const string& name) : Noble(name,0) {
    }
    void Lord::display(ostream& os) const {
        os << name << " has an army of size: " << army.size() << endl;
        for (Protector* p : army) {
            p->display();
        }
    }
    const string& Lord::getName() const { return name; }
    double Lord::getsum() const {
        double sum = 0;
        for (Protector *p: army) {
            sum += p->getStrength();
        }
        return sum;
    }
    void Lord::runaway(Protector& p) {
        size_t idx = findwarrior(p.getName(), army);
        if (idx == army.size() - 1) { // warrior at last index.
            army.pop_back();
        }
        else if (idx < army.size() - 1) { // warrior is not at the last index.
            for (size_t i = idx; idx < army.size(); ++idx) {
                army[idx] = army[idx + 1];
            }
            army.pop_back();
        }
    }
    void Lord::makezero() {
        for (Protector *p: army) {
            p->makezero();
        }
    }
    size_t Lord::findwarrior(const string& name, const vector<Protector*>& army) {
        for (size_t i = 0; i < army.size(); ++i) {
            if (name == army[i]->getName()) {
                return i;
            }
        }
        return army.size();
    }
    void Lord::defend() {
        cout << " says: Take that in the name of my lord, " << name << endl;
    };
    void Lord::hires(Protector& p) {
        if (p.getLord() == nullptr && isAlive) {
            p.hired(this);
            return army.push_back(&p);
        }
        //cout << "Protector already hired\n";
    }
    void Lord::fires(Protector& p) {
        size_t idx = findwarrior(p.getName(), army);
        if (idx == army.size() || !isAlive) { // warrior not owned.
            cout << name << " failed to fire " << p.getName() << endl;
        }
        else if (idx == army.size() - 1) { // warrior owned
            cout << p.getName() << ", you don't work for me any more! -- " << name << endl;
            army.pop_back();
            p.fired();
        }
        else if (idx < army.size() - 1) { // warrior is not at the last index.
            cout << p.getName() << ", you don't work for me any more! -- " << name << endl;
            for (size_t i = idx; idx < army.size(); ++idx) {
                army[idx] = army[idx+1];
            }
            army.pop_back();
            p.fired();
        }
    }
    void Lord::changestrength(double num1, double num2) {
        for (Protector* p : army) {
            p->changestrength(num1, num2);
        }
    }
    void Lord::battling() {
        for (Protector* p : army) {
            p->battleCry();
        }
    }
//PersonWithStrengthToFight Class
    PersonWithStrengthToFight::PersonWithStrengthToFight(const string& name, double strength) : Noble(name, strength) {
    }
    void PersonWithStrengthToFight::display(ostream& os) const {
        os << name << " has strength: " << strength << endl;
    }
    double PersonWithStrengthToFight::getsum() const {
        return strength;
    }
    void PersonWithStrengthToFight::makezero() {
        strength = 0;
    }
    void PersonWithStrengthToFight::changestrength(double num1, double num2) {
        strength *= (1-(num1/num2));
    }
    ostream& operator<<(ostream& os, const Noble& rhs) {
        rhs.display(os);
        return os;
    }
}