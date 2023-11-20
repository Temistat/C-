//
// Created by Admin on 4/13/2023.
// Temiloluwa Omomuwasan section b homework 7 too2007

#ifndef PROTECTOR_H
#define PROTECTOR_H
#include <iostream>
#include "Noble.h"


namespace Warriorcraft{
    class Lord;
    class Protector {
    public:
        Protector(const std::string &name, double strength);
        void display();
        virtual void battleCry();
        const std::string &getName() const;
        double getStrength() const;
        Lord* getLord();
        void hired(Lord* l);
        void fired();
        void makezero();
        void changestrength(double num1, double num2);
        bool runaway();
    protected:
        std::string name;
        double strength;
        Lord* lord;
    };
    class Wizard : public Protector {
    public:
        Wizard(const std::string &name, double strength);
        void battleCry();
    };
    class Warrior : public Protector {
    public:
        Warrior(const std::string &name, double strength);
    };
    class Archer : public Warrior {
    public:
        Archer(const std::string &name, double strength);
        void battleCry();
    };
    class Swordsman : public Warrior {
    public:
        Swordsman(const std::string &name, double strength);
        void battleCry();
    };
}
#endif //PROTECTOR_H
