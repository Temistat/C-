//
// Created by Admin on 6/16/2023.
//
#include <ostream>
#include <vector>
#ifndef LAB_6_FOOD_H
#define LAB_6_FOOD_H
class Food {
    std::string name;
    std::vector<std::string> ingredients;
public:
    Food(std::string name) : name(name) {}
    friend std::ostream& operator<<(std::ostream& os, const Food& rhs);
    std::string getName() const;
    std::string getIngredients() const;
};
#endif //LAB_6_FOOD_H
