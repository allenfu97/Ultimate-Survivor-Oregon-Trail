#include <iostream> 
#include <iomanip>
#include <string>
#include "Player.h"

using namespace std;

Player::Player()
{
    name = "";
    health = 100;
    days_survived = 0; 
    infamy = 0;
    wakefulness = 5;
}
Player::Player(string name_param,
            int health_param,
            int days_survived_param, 
            int infamy_param, 
            int wakefulness_param)
{
    setName(name_param);
    setHealth(health_param);
    setDays_survived(days_survived_param);
    setInfamy(infamy_param);
    setWakefulness(wakefulness_param);
}

//setters
void Player::setName(string x)
{
    name = x;
}
void Player::setHealth(int x)
{
    health = x;
}
void Player::setDays_survived(int x)
{
    days_survived = x;
}
void Player::setInfamy(int x)
{
    infamy = x;
}
void Player::setWakefulness(int x)
{
    wakefulness = x;
}

//getters--------------------------------------------------
string Player::getName()
{
    return name;
}
int Player::getHealth()
{
    return health;
}
int Player::getDays_survived()
{
    return days_survived;
}
int Player::getInfamy()
{
    return infamy;
}
int Player::getWakefulness()
{
    return wakefulness;
}