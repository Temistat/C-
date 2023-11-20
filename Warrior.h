//
// Temiloluwa Omomuwasan too2007 section B
//

#ifndef WARRIOR_H
#define WARRIOR_H

#include <iostream>
#include <string>

namespace WarriorCraft {
    class Noble;

    class Warrior{
        friend std::ostream& operator<<(std::ostream& os, const Warrior& rhs);
    public:
        Warrior(const std::string& name, int num);
        void employed(Noble* n);
        void unemployed() ;
        bool isHired() const ;
        int getnum() const;
        const std::string getname() const;
        void makezero() ;
        void changestrength(double num1, double num2);
        bool runaway();

    private:
        bool ishired;
        std::string name;
        int num;
        Noble* noble;
    };
}
#endif
