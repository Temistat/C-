#include "Rational.h"
#include <iostream>

using namespace std;
namespace CS2124{
    Rational::Rational(int numerator, int denominator) : numerator(numerator), denominator(denominator){
        normalize();
    }

    int Rational::lcm(int x, int y) {
        while (y != 0) {
            int temp = x % y;
            x = y;
            y = temp;
        }
        return x;
    } //gets lowest common denominatior1/

    void Rational::normalize() {
        int reduceFrac = 0;
        if (denominator > numerator) {
            reduceFrac = lcm(denominator, numerator);
        }
        else if (denominator < numerator) {
            reduceFrac = lcm(numerator, denominator);
        }
        else {
            reduceFrac = lcm(numerator, denominator);
        }
        numerator /= reduceFrac;
        denominator /= reduceFrac;
        if (numerator < 0 && denominator < 0) {
            numerator*=(-1);
            denominator*=(-1);
        }
        else if (numerator > 0 && denominator < 0){
            numerator*=(-1);
            denominator*=(-1);
        }
        if (numerator == 0 || denominator == 0 ) {
            numerator = 0;
            denominator = 1;
        }
    } //reduces the fraction to its lowest form

    Rational Rational::operator+=(const Rational& rhs) {
        numerator = numerator*rhs.denominator + rhs.numerator*denominator;
        denominator *= rhs.denominator;
        normalize();
        return *this;
    }

    Rational& Rational::operator++() {
        ++numerator;
        normalize();
        return *this;
    }

    Rational Rational::operator++(int) {
        Rational result(*this);
        ++numerator;
        normalize();
        return result;
    }

    Rational::operator bool() const {
        return numerator != 0;
    }

    ostream& operator<<(ostream& os, const Rational& rhs) {
        os << rhs.numerator << "/" << rhs.denominator << endl;
        return os;
    }

    istream& operator>>(istream& is, Rational& rhs) {
        char s;
        is >> rhs.numerator >> s >> rhs.denominator;
        rhs.normalize();
        return is;
    }

    Rational operator+(const Rational& lhs, const Rational& rhs) {
        Rational result(lhs);
        result += rhs;
        result.normalize();
        return result;
    }

    bool operator==(const Rational& lhs, const Rational& rhs) {
        return lhs.numerator == rhs.numerator && lhs.denominator == rhs.denominator;
    }

    bool operator<(const Rational& lhs, const Rational& rhs) {
        return (lhs.numerator*rhs.denominator) < (lhs.denominator * rhs.numerator);
    }

//pre-decrement
    Rational& operator--(Rational& rhs) {
        rhs = rhs + (-1);
        return rhs;
    }

//post-decrement
    Rational operator--(Rational& rhs, int) {
        Rational result(rhs);
        rhs = rhs + (-1);
        return result;
    }

    bool operator!=(const Rational& lhs, const Rational& rhs) {
        return !(lhs == rhs);
    }

    bool operator<=(const Rational& lhs, const Rational& rhs) {
        return (lhs == rhs) || (lhs < rhs);
    }

    bool operator>(const Rational& lhs, const Rational& rhs) {
        return !(lhs <= rhs);
    }

    bool operator>=(const Rational& lhs, const Rational& rhs) {
        return !(lhs < rhs);
    }
}
