#include "espresso_based.h"

void EspressoBased::brew() {}

std::vector<Ingredient*>& EspressoBased::get_ingredients()
{
    return this->ingredients;
}

EspressoBased::EspressoBased()
{
    this->name = "";
    this->ingredients = {};
}

EspressoBased::EspressoBased(const EspressoBased& esp)
{
    this->name = esp.name;
    this->ingredients = {};
    for(const auto &i: esp.ingredients)
    {
        auto p_cinnamon = dynamic_cast<Cinnamon*>(i);
        if(p_cinnamon)
        {
            this->ingredients.push_back(new Cinnamon(*p_cinnamon));
            continue;
        }
        auto p_chocolate = dynamic_cast<Chocolate*>(i);
        if(p_chocolate)
        {
            this->ingredients.push_back(new Chocolate(*p_chocolate));
            continue;
        }
        auto p_sugar = dynamic_cast<Sugar*>(i);
        if(p_sugar)
        {
            this->ingredients.push_back(new Sugar(*p_sugar));
            continue;
        }
        auto p_cookie = dynamic_cast<Cookie*>(i);
        if(p_cookie)
        {
            this->ingredients.push_back(new Cookie(*p_cookie));
            continue;
        }
        auto p_espresso = dynamic_cast<Espresso*>(i);
        if(p_espresso)
        {
            this->ingredients.push_back(new Espresso(*p_espresso));
            continue;
        }
        auto p_milk = dynamic_cast<Milk*>(i);
        if(p_milk)
        {
            this->ingredients.push_back(new Milk(*p_milk));
            continue;
        }
        auto p_milkFoam = dynamic_cast<MilkFoam*>(i);
        if(p_milkFoam)
        {
            this->ingredients.push_back(new MilkFoam(*p_milkFoam));
            continue;
        }
        auto p_water = dynamic_cast<Water*>(i);
        if(p_water)
        {
            this->ingredients.push_back(new Water(*p_water));
            continue;
        }
    }
}

EspressoBased::~EspressoBased()
{
    for(auto &i: this->ingredients)
    {
        delete i;
    }
    this->ingredients.clear();
}
