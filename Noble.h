//
// Created by Admin on 4/13/2023.
// Temiloluwa Omomuwasan section b homework 7 too2007

#ifndef NOBLE_H
#define NOBLE_H
#include <iostream>
#include <vector>

namespace Warriorcraft {
    class Protector;
    class Noble {
    public:
        Noble(const std::string& name, double strength);
        virtual void makezero(); // to make all the warrior strength zero when they lose a battle.
        virtual double getsum() const; //gets the sum of the all warriors.
        virtual void changestrength(double num1, double num2);
        virtual void display(std::ostream& os) const;
        virtual void battling();
        virtual void defend();
        void battle(Noble& n);
    protected:
        std::string name;
        double strength;
        bool isAlive;
    };

    class Lord : public Noble {
    public:
        Lord(const std::string& name);
        void display(std::ostream& os) const;
        const std::string& getName() const;
        double getsum() const;
        void makezero();
        size_t findwarrior(const std::string& name, const std::vector<Protector*>& army);
        void hires(Protector& p);
        void fires(Protector& p);
        void changestrength(double num1, double num2);
        void battling();
        void defend();
        void runaway(Protector& p);
    private:
        std::vector<Protector*> army;
    };

    class PersonWithStrengthToFight : public Noble {
    public:
        PersonWithStrengthToFight(const std::string& name, double strength);
        void display(std::ostream& os) const;
        double getsum() const;
        void makezero();
        void changestrength(double num1, double num2);
    };

    std::ostream& operator<<(std::ostream& os, const Noble& rhs);
}

#endif //NOBLE_H
