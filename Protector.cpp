//
// Created by Admin on 4/13/2023.
// Temiloluwa Omomuwasan section b homework 7 too2007

#include "Protector.h"
#include "Noble.h"
#include <iostream>
#include <string>
#include  <vector>
using namespace std;

namespace Warriorcraft {
    Protector::Protector(const string &name, double strength) : name(name), strength(strength), lord(nullptr) {
    }

    void Protector::display() {
        cout << "\t" << name << " has strength " << strength << endl;
    }

    void Protector::battleCry() {};

    const string &Protector::getName() const { return name; }

    double Protector::getStrength() const { return strength; }

    Lord *Protector::getLord() { return lord; }

    void Protector::hired(Lord* l) {
        lord = l;
    }

    void Protector::fired() {
        lord = nullptr;
    }

    void Protector::makezero() {
        strength = 0;
    }

    void Protector::changestrength(double num1, double num2) {
        double num3 = 1 - (num1 / num2);
        strength *= num3;
    }

    bool Protector::runaway() {
        if (lord != nullptr) {
            cout << name << " flees in terror, abandoning his lord, " << lord->getName() << endl;
            lord->runaway(*this);
            lord = nullptr;
            return true;
        }
        return false;
    }

//Wizard Class
    Wizard::Wizard(const string &name, double strength) : Protector(name, strength) {
    }

    void Wizard::battleCry() {
        cout << "POOF" << endl;
    }

//Warrior Class
    Warrior::Warrior(const string &name, double strength) : Protector(name, strength) {
    }

//Archer Class
    Archer::Archer(const string &name, double strength) : Warrior(name, strength) {
    }

    void Archer::battleCry() {
        cout << "TWANG " << name;
        lord->defend();
    }

//Swordman Class
    Swordsman::Swordsman(const string &name, double strength) : Warrior(name, strength) {
    }

    void Swordsman::battleCry() {
        cout << "CLANG " << name;
        lord->defend();
    }
}