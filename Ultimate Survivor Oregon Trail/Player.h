#ifndef PLAYER_H //these have to be capitalized for some reason
#define PLAYER_H //not sure why this one is blue
#include <string>

using namespace std;

class Player
{
private:
    string name;
    int health;
    int days_survived;
    int infamy;
    int wakefulness;

public:
    Player();
    Player(string name_param,
            int health_param,
            int days_survived_param, 
            int infamy_param, 
            int wakefulness_param);
    
    void setName(string x);
    void setHealth(int x);
    void setDays_survived(int x);
    void setInfamy(int x);
    void setWakefulness(int x);
    
    string getName();
    int getHealth();
    int getDays_survived();
    int getInfamy();
    int getWakefulness();
};
#endif