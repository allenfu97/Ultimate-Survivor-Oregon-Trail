#include <iostream> //always include this
#include <ctime> //for accessing system clock
#include <fstream> //to read or write files
#include <cstdlib> //for random
#include <cctype> //if you wanna use isdigit, isalpha, islower, isupper, isalnum, isspace
using namespace std;

#include "Game.h"

//makes sure that the user input is just digits, returns 0 otherwise
string inputCheck(string x)
{
    if (x == "")
        {
            return "0";
        }
    for (int i = 0; i < x.length(); i++)
    {
        if (isdigit(x[i]) == false)
        {
            return "0";
        }
    }
    
    return x;
}

int main(int argc, char const *argv[]) //no idea what this is
{
    srand(time(0)); //sets rng seed to the system clock
    Game game; //making the game object
    game.createAllCaravan();//making all caravans
    
    string choice  = "";
    string choice2 = "";
    string choice3 = "";
    
    string storage;
    bool caravan_check;
    
    game.introduction();
    
    while (choice != "99") 
    {
        //check for death
        if (game.death() == true)
        {
            choice = "99"; //while loop will end
        }
        
        //make sure that invalid input doesn't allow for caravan rechecking
        if (storage != "no")
        {
            caravan_check = game.caravanCheck();
        }
        storage = "";//reset storage
        
        game.mainMenu();
        
        getline(cin, choice);
        choice = inputCheck(choice);
        
        switch (stoi(choice)) 
        {
            case 1: //observe the trail 
                if (caravan_check == true)
                {
                    while (choice2 != "4")
                    {
                        game.caravanMenu();
                        
                        getline(cin, choice2);
                        choice2 = inputCheck(choice2);
                        switch (stoi(choice2)) 
                        {
                            case 1: 
                                
                                while (choice3 != "6")
                                {
                                    game.stealOptions();
                                    getline(cin, choice3);
                                    choice3 = inputCheck(choice3);
                                    switch (stoi(choice3))
                                    {
                                        case 1: //steal food
                                        {
                                            game.stealFood();
                                            
                                            game.incrementDay_time();//only do this if action is taken
                                            choice3 = "6";//exit steal loop
                                            choice2 = "4"; //exit caravan interaction loop
                                            break;
                                        }
                                        case 2: //steal coins
                                        {
                                            game.stealCoins();
                                            
                                            game.incrementDay_time();//only do this if action is taken
                                            choice3 = "6";//exit steal loop
                                            choice2 = "4"; //exit caravan interaction loop
                                            break;
                                        }
                                        case 3: //steal animal parts
                                        {
                                            game.stealAnimalParts();
                                            
                                            game.incrementDay_time();//only do this if action is taken
                                            choice3 = "6";//exit steal loop
                                            choice2 = "4"; //exit caravan interaction loop
                                            break;
                                        }
                                        case 4: //steal general supplies
                                        {
                                            game.stealGeneralSupplies();
                                            
                                            game.incrementDay_time();//only do this if action is taken
                                            choice3 = "6";//exit steal loop
                                            choice2 = "4"; //exit caravan interaction loop
                                            break;
                                        }
                                        case 5: //steal weaponry
                                        {
                                            game.stealWeaponry();
                                            
                                            game.incrementDay_time();//only do this if action is taken
                                            choice3 = "6";//exit steal loop
                                            choice2 = "4"; //exit caravan interaction loop
                                            break;
                                        }
                                        case 6: //never mind, exit steal options
                                        {
                                            cout << "okey doke" << endl;
                                            break;
                                        }
                                        default:
                                            cout << "invalid input" << endl;
                                    }
                                }
                                choice3 = "";//reset choice3
                                
                                if (game.death() == true)
                                {
                                    choice = "99"; //while loop will end
                                    choice2 = "4";
                                }
                                
                                
                                
                                
                                break;
                            case 2: //sabotage
                                if (game.s_resourceCheck() == true)
                                {
                                    game.sabotage(); //xxx if successful, recalculate survivial and mobility.. if 
                                    //you wanna keep tat difficultiy
                                    
                                    if (game.death() == true)
                                    {
                                        choice = "99"; //while loop will end
                                        choice2 = "4";
                                    }
                                    
                                    game.incrementDay_time();//only do this if action is taken
                                    choice2 = "4";//exit caravan interaction loop
                                }
                                else
                                {
                                    cout << "Not enough resources" << endl << endl;
                                }
                                break;
                            case 3: //assassinate
                                if (game.a_resourceCheck() == true)
                                {
                                    game.assassinate(); 
                                    
                                    if (game.death() == true)
                                    {
                                        choice = "99"; //while loop will end
                                        choice2 = "4";
                                    }
                                    
                                    game.incrementDay_time();//only do this if action is taken
                                    choice2 = "4";//exit caravan interaction loop
                                }
                                else
                                {
                                    cout << "Not enough resources" << endl << endl;
                                }
                                break;
                            case 4: //never mind
                                cout << "never mind" << endl;
                                break;
                            default:
                                cout << "invalid input" << endl;
                        }
                    }
                    choice2 = ""; //reset choice2
                    
                }
                else
                {
                    cout << "I said, there's nothing on the trail" << endl;
                }
                break;

            case 2: //hunt in the forest
                game.hunt();
                game.incrementDay_time();
                break;
            case 3: //rest in hideout
                game.incrementDay_time();//reduce wakefulness -1
                game.rest();//then add +3
                
                break;
            case 4: //save/load file
                break;
            case 5: //help 
                game.help();
                break;
            case 10: //print stats of a caravan. remember to remove this later//xxxxxxx
                cout << "Caravan Index: ";
                getline(cin, storage);
                game.printCaravanIndex(stoi(storage));
                break;
            case 99: //quit
                cout << "Later. I hope you remembered to save, because I didn't" << endl;
                break;
            default: 
                cout << "invalid input" << endl;
                storage = "no";
        }
        
        cout << endl;
        if (game.death() == true)
        {
            choice = "99"; //while loop will end
        }
        if (game.getNext_caravan() == 50)
        {
            choice = "99"; //while loop will end
            cout << "All 50 caravans have passed by." << endl;
            cout << "Thanks for playing." << endl;
        }
    }
    
    game.readWriteFile();
    
    return 0;
}