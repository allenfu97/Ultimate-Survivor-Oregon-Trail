#ifndef CARAVAN_H //these have to be capitalized for some reason
#define CARAVAN_H //not sure why this one is blue
#include <string>

using namespace std;

class Caravan
{
private:
    int wagons;
    int oxen;
    int people;
    bool player_perception;//does the caravan know that the player exists?
    
    //hidden info
    int c_food;
    int c_coins;
    int c_animal_parts;
    int c_general_supplies;
    int c_weaponry;
    bool player_spy;//does the player has access to this hidden info?
    
    bool mobility; //whether or not they can move on
    int survival; // % chance of survival, determined by their other stats
    bool presence; //whether or not they are on the trail
    int days_on_trail;
    
public:
    //default constructor and parameterized constructor
    Caravan();
    Caravan(int wagons_param, 
            int oxen_param, 
            int people_param, 
            bool player_perception, 
            int c_food_param, 
            int c_coins_param, 
            int c_animal_parts_param, 
            int c_general_supplies_param,
            int c_weaponry_param,
            bool player_spy_param,
            bool mobility_param,
            int survival_param,
            bool presence_param,
            int days_on_trail_param);
    
    //setters
    void setWagons(int x);
    void setOxen(int x);
    void setPeople(int x);
    void setPlayer_perception(bool x);
    
    void setC_food(int x);
    void setC_coins(int x);
    void setC_animal_parts(int x);
    void setC_general_supplies(int x);
    void setC_weaponry(int x);
    void setPlayer_spy(bool x);
    
    void setMobility(bool x);
    void setSurvival(int x);
    void setPresence(bool x);
    void setDays_on_trail(int x);
    
    //getters
    int getWagons();
    int getOxen();
    int getPeople();
    bool getPlayer_perception();
    
    int getC_food();
    int getC_coins();
    int getC_animal_parts();
    int getC_general_supplies();
    int getC_weaponry();
    bool getPlayer_spy();
    
    bool getMobility();
    int getSurvival();
    bool getPresence();
    int getDays_on_trail();
    
    //caravan calculations
    //void calculate survival or something like that, calc mobility
    
    //returns the appropriate value of caravan mobility
    //DOES NOT SET IT
    bool calcMobility();
    
    void createEasyCaravan();
    void createMediumCaravan();
    void createHardCaravan();
};

#endif