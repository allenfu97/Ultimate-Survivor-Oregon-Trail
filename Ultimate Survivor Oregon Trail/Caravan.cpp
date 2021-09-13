#include <iostream> 
#include <iomanip>
#include <string>
#include "Caravan.h"

using namespace std;

Caravan::Caravan()
{
    wagons = 0;
    oxen = 0;
    people = 0;
    player_perception = false;
    
    c_food = 0;
    c_coins = 0;
    c_animal_parts = 0;
    c_general_supplies = 0;
    c_weaponry = 0;
    player_spy = false;
    
    mobility = false;
    survival = 0;
    presence = false;
    days_on_trail = 0;
}

Caravan::Caravan(int wagons_param, 
                int oxen_param, 
                int people_param, 
                bool player_perception_param,
                int c_food_param,
                int c_coins_param,
                int c_animal_parts_param,
                int c_general_supplies_param,
                int c_weaponry_param,
                bool player_spy_param,
                bool mobility_param, 
                int survival_param,
                bool presence_param, 
                int days_on_trail_param)
{
    setWagons(wagons_param);
    setOxen(oxen_param);
    setPeople(people_param);
    setPlayer_perception(player_perception_param);
    
    setC_food(c_food_param);
    setC_coins(c_coins_param);
    setC_animal_parts(c_animal_parts_param);
    setC_general_supplies(c_general_supplies_param);
    setC_weaponry(c_weaponry_param);
    setPlayer_spy(player_spy_param);
    
    setMobility(mobility_param);
    setSurvival(survival_param);
    setPresence(presence_param);
    setDays_on_trail(days_on_trail_param);
}

//setters
void Caravan::setWagons(int x)
{
    wagons = x;
}
void Caravan::setOxen(int x)
{
    oxen = x;
}
void Caravan::setPeople(int x)
{
    people = x;
}
void Caravan::setPlayer_perception(bool x)
{
    player_perception = x;
}

void Caravan::setC_food(int x)
{
    c_food = x;
}
void Caravan::setC_coins(int x)
{
    c_coins = x;
}
void Caravan::setC_animal_parts(int x)
{
    c_animal_parts = x;
}
void Caravan::setC_general_supplies(int x)
{
    c_general_supplies = x;
}
void Caravan::setC_weaponry(int x)
{
    c_weaponry = x;
}
void Caravan::setPlayer_spy(bool x)
{
    player_spy = x;
}
void Caravan::setMobility(bool x)
{
    mobility = x;
}
void Caravan::setSurvival(int x)
{
    survival = x;
}
void Caravan::setPresence(bool x)
{
    presence = x;
}
void Caravan::setDays_on_trail(int x)
{
    days_on_trail = x;
}

//getters-------------------------------------------------
int Caravan::getWagons()
{
    return wagons;
}
int Caravan::getOxen()
{
    return oxen;
}
int Caravan::getPeople()
{
    return people;
}
bool Caravan::getPlayer_perception()
{
    return player_perception;
}

int Caravan::getC_food()
{
    return c_food;
}
int Caravan::getC_coins()
{
    return c_coins;
}
int Caravan::getC_animal_parts()
{
    return c_animal_parts;
}
int Caravan::getC_general_supplies()
{
    return c_general_supplies;
}
int Caravan::getC_weaponry()
{
    return c_weaponry;
}
bool Caravan::getPlayer_spy()
{
    return player_spy;
}
bool Caravan::getMobility()
{
    return mobility;
}
int Caravan::getSurvival()
{
    return survival;
}
bool Caravan::getPresence()
{
    return presence;
}
int Caravan::getDays_on_trail()
{
    return days_on_trail;
}

//calculations-----------------------------------------------

bool Caravan::calcMobility()
{
                                                        //not enough food for everyone
    if (wagons == 0 || oxen == 0 || people == 0 || survival <= 0 || c_food <= people)
    {
        return false;
    }
    else 
    {
        return true;
    }
}

void Caravan::createEasyCaravan()
{
    wagons = (1 + rand() % 3); //generates random numbers 1-3
    oxen = (2 + rand() % 3); //2-4
    people = (4 + rand() % 5); //4-8
    player_perception = false;
    
    c_food = people * 3 + (rand() % 6); //3 times number of people, + up to 5
    c_coins = (10 + rand() % 11);          //10-20
    c_animal_parts = (5 + rand() % 11); //5-15
    c_general_supplies = (5 + rand() % 11); //5-15
    c_weaponry = (5 + rand() % 11); //5-15
    player_spy = false;
    mobility = true; 
    survival = 90; 
    presence = false;
    days_on_trail = 0;
}

void Caravan::createMediumCaravan()
{
    wagons = (3 + rand() % 3); //3-5
    oxen = (4 + rand() % 3); //4-6
    people = (5 + rand() % 8); //5-12
    player_perception = false;
    
    c_food = people * 5 + (rand() % 11); //5 times number of people, + up to 10
    c_coins = (20 + rand() % 21);          //20-40
    c_animal_parts = (10 + rand() % 11); //10-20
    c_general_supplies = (10 + rand() % 11); //10-20
    c_weaponry = (10 + rand() % 11); //10-20
    player_spy = false;
    mobility = true; 
    survival = 95; 
    presence = false;
    days_on_trail = 0;
}

void Caravan::createHardCaravan()
{
    wagons = (5 + rand() % 3); //5-7
    oxen = (6 + rand() % 3); //6-8
    people = (5 + rand() % 8); //5-12
    player_perception = false;
    
    c_food = people * 7 + (rand() % 6); //7 times number of people, + up to 5
    c_coins = (30 + rand() % 21);        //30-50
    c_animal_parts = (15 + rand() % 11); //15-25
    c_general_supplies = (15 + rand() % 11); //15-25
    c_weaponry = (15 + rand() % 11); //15-25
    player_spy = false;
    mobility = true; 
    survival = 100; 
    presence = false;
    days_on_trail = 0;
}

/* mobility and survival calculations
    
    
    survival = 0 instantly if
    - wagons = 0
    - people = 0
    - c_food = 0
    
    huge decrease to survival
    - 2 * c_food < people
    - c_general_supplies < people
    - c_weaponry <= 3
    - people <= 2
    
    */