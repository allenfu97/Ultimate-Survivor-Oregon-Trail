#ifndef INVENTORY_H //these have to be capitalized for some reason
#define INVENTORY_H //not sure why this one is blue
#include <string>
using namespace std;

class Inventory
{
private:
    int coins;
    int food;
    int animal_parts;
    int general_supplies;
    int weaponry;
    
    
public:
    //default constructor
    Inventory();
    
    //parameterized constructor
    Inventory(  int coins_param, 
                int food_param, 
                int animal_parts_param, 
                int general_supplies_param, 
                int weaponry_param);
    
    //setters
    void setCoins(int x);
    void setFood(int x);
    void setAnimal_parts(int x);
    void setGeneral_supplies(int x);
    void setWeaponry(int x);
    // void setInventory_space(int x);
    // void setMax_inventory_space(int x);
    
    //getters
    int getCoins();
    int getFood();
    int getAnimal_parts();
    int getGeneral_supplies();
    int getWeaponry();
    // int getInventory_space();
    // int getMax_inventory_space();
    
};

#endif 