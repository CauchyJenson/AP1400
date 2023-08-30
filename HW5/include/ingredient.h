#ifndef INGREDIENT_H
#define INGREDIENT_H
#include<string>

class Ingredient
{
public:
    double get_price_unit();
    size_t get_units();
    std::string get_name();

    double price();
    

protected:
    Ingredient(double price_unit, size_t units);

    double price_unit;
    size_t units;
    std::string name;
};

double Ingredient::get_price_unit(){
    return price_unit;
}

size_t Ingredient::get_units(){
    return units;
}

double Ingredient::price(){
    return this->get_price_unit()*this->get_units();
}

std::string Ingredient::get_name(){
    return name;
}

#endif // INGREDIENT_H