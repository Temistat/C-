//
// Created by Admin on 3/24/2023.
//

#ifndef RATIONAL_H
#define RATIONAL_H
#include <iostream>
#include <string>

namespace CS2124 {
    class Rational {
        friend std::ostream &operator<<(std::ostream &os, const Rational &rhs);

        friend std::istream &operator>>(std::istream &is, Rational &rhs);

    public:
        Rational(int numerator = 1, int denominator = 1);

        int lcm(int x, int y);

        void normalize();

        Rational operator+=(const Rational &rhs);

        friend bool operator==(const Rational &lhs, const Rational &rhs);

        friend bool operator<(const Rational &lhs, const Rational &rhs);

        Rational &operator++();

        Rational operator++(int);

        explicit operator bool() const;

    private:
        int numerator;
        int denominator;
    };

    Rational operator+(const Rational& lhs, const Rational& rhs);
    bool operator==(const Rational& lhs, const Rational& rhs);
    bool operator<(const Rational& lhs, const Rational& rhs);
//pre-decrement
    Rational& operator--(Rational& rhs);
//post-decrement
    Rational operator--(Rational& rhs, int);
    bool operator!=(const Rational& lhs, const Rational& rhs);
    bool operator<=(const Rational& lhs, const Rational& rhs);
    bool operator>(const Rational& lhs, const Rational& rhs);
    bool operator>=(const Rational& lhs, const Rational& rhs);
}
#endif
