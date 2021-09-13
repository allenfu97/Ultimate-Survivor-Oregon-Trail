#ifndef GAME_H //these have to be capitalized for some reason
#define GAME_H //not sure why this one is blue
#include <string>

#include "Player.h"
#include "Caravan.h"
#include "Inventory.h"


using namespace std;

class Game
{
private:
    Player player;
    Caravan caravan[50];
    Inventory inventory;
    int day_time;
    int days_since_last_c;
    int next_caravan;
    
public:
    //constructor
    Game();
    
    //parameterized constuctor //xxxxxxxxxxx make this at the end
    
    void readWriteFile();
    
    //game variables{
    
    //day time{
    void setDay_time(int x);
    int getDay_time();
    void displayDay_time();
    void incrementDay_time();
    //}
    
    //days since last caravan{
    void setDays_since_last_c(int x);
    int getDays_since_last_c();
    //}
    
    //next caravan{
    void setNext_caravan(int x);
    int getNext_caravan();
    //}
    
    //}  end of game variable functions
    
    //text display functions{
    void help();
    void introduction();
    void allStats();
    void playerStats();
    void inventoryStats();
    void mainMenu();
    bool death();//checks for death
    
    bool caravanCheck();//checks if next caravan is here or nah, random chance. Called in main
    
    void caravanStats();
    void caravanInteractions();
    void caravanMenu();
    //}
    
    //caravan --------
    void caravanTime();
    void caravanDeath();
    
    //secretive interactions
    //not complete xxxxxxxxxxxxxx{
    void stealOptions();
    void stealFood();
    void stealCoins();
    void stealAnimalParts();
    void stealGeneralSupplies();
    void stealWeaponry();
    
    void damage();
    void sabotage();
    bool s_resourceCheck();
    
    void assassinate();
    bool a_resourceCheck();
    //}
    
    void hunt();
    
    //rest mechanics------------------------
    void rest();
    
    //caravan creation and printing{
    void createAllCaravan();
    void printAllCaravan(); //just for testing
    void printCaravanIndex(int x);//just for testing
    //}
    
};
#endif