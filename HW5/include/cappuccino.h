#ifndef CAPPUCCINO
#define CAPPUCCINO
#include"ingredient.h"
#include"sub_ingredients.h"
#include"espresso_based.h"
#include<vector>
#include<string>

class Cappuccino: public EspressoBased
{
public:
    Cappuccino();
    Cappuccino(const Cappuccino& cap);
	~Cappuccino();
    void operator=(const Cappuccino& cap);

    virtual std::string get_name();
    virtual double price();

    void add_side_item(Ingredient* side);
    std::vector<Ingredient*>& get_side_items();

private:
    std::vector<Ingredient*> side_items;

};



#endif // CAPPUCCINO