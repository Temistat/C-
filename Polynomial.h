//
// Created by Admin on 5/1/2023.
// Temiloluwa Omomwuasan, section B, homework 8, too2007

#ifndef POLYNOMIAL_H
#define POLYNOMIAL_H
#include <iostream>
#include <vector>

class Polynomial {
public:
    friend std::ostream& operator<<(std::ostream& os, const Polynomial& rhs);
    Polynomial(const std::vector<int> numbers = {0});
    Polynomial& operator+=(const Polynomial& rhs);
    int evaluate(int value);
    friend bool operator==(const Polynomial& lhs, const Polynomial& rhs);
    ~Polynomial ();
    Polynomial(const Polynomial& rhs);
    Polynomial& operator=(const Polynomial& rhs);
private:
    struct Node {
        int data = 0;
        Node* next = nullptr;
    };
    std::vector<int> numbers;
    int degree = 0;
    Node* head = nullptr;
};
Polynomial operator+(Polynomial& lhs, Polynomial& rhs);
bool operator==(const Polynomial& lhs, const Polynomial& rhs);
bool operator!=(const Polynomial& lhs, const Polynomial& rhs);
void doNothing(Polynomial temp);


#endif //POLYNOMIAL_H
