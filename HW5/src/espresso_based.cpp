#include "espresso_based.h"

std::string EspressoBased::get_name(){
    return this->name;   
}

double EspressoBased::price(){
    auto list_ingredients = this->get_ingredients();
    double sum = 0.0;
    for(auto i: list_ingredients){
        sum += i->price();
    }
    return sum;
}

std::vector<Ingredient*>& EspressoBased::get_ingredients(){
    return this->ingredients;
}

void EspressoBased::brew(){
    // addittion step
    // I don't know what to do.
    // so I just do nothing.
}

EspressoBased::EspressoBased(): ingredients({}), name(""){}

EspressoBased::EspressoBased(const EspressoBased& esp)
    : ingredients(esp.ingredients), name(esp.name){}

void EspressoBased::operator=(const EspressoBased& esp){
    this->ingredients = esp.ingredients;
    this->name = esp.name;
}

EspressoBased::~EspressoBased()
{
    for(const auto& i : ingredients)
        delete i;
    ingredients.clear();
}

