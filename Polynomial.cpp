//
// Created by Admin on 5/1/2023.
// Temiloluwa Omomwuasan, section B, homework 8, too2007

#include "Polynomial.h"
#include <iostream>
#include <vector>
#include <string>
using namespace std;

ostream& operator<<(ostream& os, const Polynomial& rhs) {
    if (rhs.degree == 0) {
        os << rhs.head->data << endl;
    }
    else if (rhs.degree > 0) {
        Polynomial::Node* curr = rhs.head;
        int count = rhs.degree;
        while (count > 1) {
            if (curr->data != 0) {
                if (curr->data == 1) {
                    os << "x^" << count << "+";
                }
                else if (curr->data == -1) {
                    os << "-x" << "+";
                }
                else {
                    os << curr->data << "x^" << count << "+";
                }
            }
            count -= 1;
            curr = curr->next;
        }
        if (curr->data != 0) {
            if (curr->data == 1) {
                os << "x" << "+";
            }
            else if (curr->data == -1) {
                os << "-x" << "+";
            }
            else {
                os << curr->data << "x" << "+";
            }
        }
        curr = curr->next;
        if (curr->data != 0) {
            os << curr->data << endl;
        }
    }
    return os;
}
Polynomial::Polynomial(const vector<int> numbers) : numbers(numbers) {
    head = new Node{numbers[0], nullptr};
    Node* prev_node = head;
    for (size_t index = 1; index < numbers.size(); ++index) {
        Node* n = new Node{numbers[index], nullptr};
        prev_node->next = n;
        prev_node = n;
    }
    degree = numbers.size() - 1;
}
Polynomial& Polynomial::operator+=(const Polynomial& rhs) {
    if (degree == rhs.degree) {
        Node* curr = head;
        Node* curr1 = rhs.head;
        while (curr) {
            curr->data += curr1->data;
            curr = curr->next;
            curr1 = curr1->next;
        }
        return *this;
    }
    else if (degree < rhs.degree) {
        int diff = rhs.degree - degree;
        for (size_t i = 0; i < diff; i++) {
            Node* temp = new Node{0, head};
            head = temp;
            ++degree;
        }
        Node* curr = head;
        Node* curr1 = rhs.head;
        while (curr) {
            curr->data += curr1->data;
            curr = curr->next;
            curr1 = curr1->next;
        }
        return *this;
    }
    else if (degree > rhs.degree) {
        int diff = degree - rhs.degree;
        Node* temp = head;
        for (size_t i = 0; i < diff; ++i) {
            temp = temp->next;
        }
        Node* curr = temp;
        Node* curr1 = rhs.head;
        while (curr) {
            curr->data += curr1->data;
            curr = curr->next;
            curr1 = curr1->next;
        }
        return *this;
    }
}
int Polynomial::evaluate(int value) {
    int result = 0;
    Node* curr = head;
    int count = degree;
    while (count > 0) {
        int num = value;
        for (size_t i = 0; i < count - 1; i++) {
            num *= value;
        }
        int add_value = curr->data * num;
        result += add_value;
        --count;
        curr = curr->next;
    }
    result += curr->data;
    return result;
}
bool operator==(const Polynomial& lhs, const Polynomial& rhs);
Polynomial::~Polynomial () {
    Node* curr = head;
    while (curr) {
        Node* prev = curr;
        curr = prev->next;
        prev = nullptr;
        delete prev;
        --degree;
    }
    delete curr;
}
Polynomial::Polynomial(const Polynomial& rhs) {
    head = new Node{rhs.head->data};
    degree = rhs.degree;
    Node* curr = head;
    Node* curr1 = rhs.head;
    while (curr1) {
        if (curr1->next == nullptr) {
            curr->next = nullptr;
        } else{
            curr->next = new Node{curr1->next->data};
        }
        curr = curr->next;
        curr1 = curr1->next;
    }
}
Polynomial& Polynomial::operator=(const Polynomial& rhs){
    if (&rhs != this) {
        Node* curr  = head;
        while (curr) {
            Node* prev = curr;
            curr = curr->next;
            prev = nullptr;
            delete prev;
            --degree;
        }
        delete curr;
        head = new Node{rhs.head->data};
        Node* curr1 = head;
        Node* curr2 = rhs.head;
        while (curr2) {
            if (curr2->next == nullptr) {
                curr1->next = nullptr;
            } else {
                curr1->next = new Node{curr2->next->data};
            }
            curr1 = curr1->next;
            curr2 = curr2->next;
        }
        degree = rhs.degree;
    }
    return *this;
}

Polynomial operator+(Polynomial& lhs, Polynomial& rhs) {
    Polynomial result(lhs);
    result += rhs;
    return result;
}

bool operator==(const Polynomial& lhs, const Polynomial& rhs) {
    if (lhs.degree == rhs.degree) {
        Polynomial::Node* curr = lhs.head;
        Polynomial::Node* curr1 = rhs.head;
        while (curr) {
            if (curr->data != curr1->data) {
                return false;
            }
            else {
                curr = curr->next;
                curr1 =curr1->next;
            }
        }
        return true;
    }
    else {
        return false;
    }
}
bool operator!=(const Polynomial& lhs, const Polynomial& rhs) {
    return !(lhs == rhs);
}

void doNothing(Polynomial temp) {}
