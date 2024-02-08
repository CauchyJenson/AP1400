#include "cappuccino.h"


Cappuccino::Cappuccino()
{
    this->name = "Cappuccino";
    this->ingredients = {};
    (this->ingredients).push_back(new Espresso{2});
    (this->ingredients).push_back(new Milk{2});
    (this->ingredients).push_back(new MilkFoam{1});
    this->side_items = {};
}

Cappuccino::Cappuccino(const Cappuccino& cap)
{
    this->name = cap.name;
    this->ingredients = {};
    for(const auto &i: cap.ingredients)
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
    this->side_items = {};
    for(const auto &i: cap.side_items)
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

Cappuccino::~Cappuccino()
{
    for(auto &i: this->ingredients)
    {
        delete i;
    }
    this->ingredients.clear();
    for(auto &i: this->side_items)
    {
        delete i;
    }
    this->side_items.clear();
}

void Cappuccino::operator=(const Cappuccino& cap)
{
    if(this == &cap)
        return;
    this->name = cap.name;
    this->ingredients = {};
    for(const auto &i: cap.ingredients)
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

std::string Cappuccino::get_name()
{
    return this->name;
}

double Cappuccino::price()
{
    double price = 0;
    for(const auto &i: this->ingredients)
    {
        price += i->price();
    }
    for(const auto &i: this->side_items)
    {
        price += i->price();
    }
    return price;
}

void Cappuccino::add_side_item(Ingredient* side)
{
    (this->side_items).push_back(side);
}

std::vector<Ingredient*>& Cappuccino::get_side_items()
{
    return this->side_items;
}
