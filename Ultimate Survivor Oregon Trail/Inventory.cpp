#include <iostream> 
#include <iomanip>
#include <string>
#include "Inventory.h"

using namespace std;

//default constructor: sets everything to stock values
Inventory::Inventory()
{
    coins = 10; 
    
    food = 5;
    animal_parts = 5;
    general_supplies = 5;
    weaponry = 5; 
    
}

//parameterized constructor
Inventory::Inventory(int coins_param, 
                    int food_param, 
                    int animal_parts_param, 
                    int general_supplies_param, 
                    int weaponry_param)
{
    setCoins(coins_param);
    setFood(food_param);
    setAnimal_parts(animal_parts_param);
    setGeneral_supplies(general_supplies_param);
    setWeaponry(weaponry_param);
}

//setters

void Inventory::setCoins(int x)
{
    coins = x;
}

void Inventory::setFood(int x)
{
    food = x;
}

void Inventory::setAnimal_parts(int x)
{
    animal_parts = x;
}

void Inventory::setGeneral_supplies(int x)
{
    general_supplies = x;
}

void Inventory::setWeaponry(int x)
{
    weaponry = x;
}

//getters---------------------------------------------------------------------
int Inventory::getCoins()
{
    return coins;
}

int Inventory::getFood()
{
    return food;
}

int Inventory::getAnimal_parts()
{
    return animal_parts;
}

int Inventory::getGeneral_supplies()
{
    return general_supplies;
}

int Inventory::getWeaponry()
{
    return weaponry;
}

