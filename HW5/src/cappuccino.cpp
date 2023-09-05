#include "cappuccino.h"

Cappuccino::Cappuccino(){
    this->ingredients = std::vector<Ingredient*>{};
    this->ingredients.push_back(new Espresso(2));
    this->ingredients.push_back(new Milk(2));
    this->ingredients.push_back(new MilkFoam(1));
}

Cappuccino::~Cappuccino()
{
    for(const auto& i : side_items)
        delete i;
    side_items.clear();
}

Cappuccino::Cappuccino(const Cappuccino& cap): EspressoBased(cap){
    for(auto i: cap.side_items){
        auto ptr_1 = dynamic_cast<Cinnamon*> (i);
        auto ptr_2 = dynamic_cast<Chocolate*> (i);
        auto ptr_3 = dynamic_cast<Sugar*> (i);
        auto ptr_4 = dynamic_cast<Cookie*> (i);
        auto ptr_5 = dynamic_cast<Espresso*> (i);
        auto ptr_6 = dynamic_cast<Milk*> (i);
        auto ptr_7 = dynamic_cast<MilkFoam*> (i);
        auto ptr_8 = dynamic_cast<Water*> (i);

        if(!ptr_1){
            auto elem_1 = new Cinnamon(i->get_units());
            this->side_items.push_back(elem_1);
        }else if(!ptr_2){
            auto elem_2 = new Chocolate(i->get_units());
            this->side_items.push_back(elem_2);
        }else if(!ptr_3){
            auto elem_3 = new Sugar(i->get_units());
            this->side_items.push_back(elem_3);
        }else if(!ptr_4){
            auto elem_4 = new Cookie(i->get_units());
            this->side_items.push_back(elem_4);
        }else if(!ptr_5){
            auto elem_5 = new Espresso(i->get_units());
            this->side_items.push_back(elem_5);
        }else if(!ptr_6){
            auto elem_6 = new Milk(i->get_units());
            this->side_items.push_back(elem_6);
        }else if(!ptr_7){
            auto elem_7 = new MilkFoam(i->get_units());
            this->side_items.push_back(elem_7);
        }else if(!ptr_8){
            auto elem_8 = new Water(i->get_units());
            this->side_items.push_back(elem_8);
        }
}