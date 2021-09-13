#include <iostream> 
#include <iomanip>
#include <string>
#include <ctime> //for accessing system clock
#include <cstdlib> //for random
#include <fstream> //to read or write files
#include <sstream> //stringstreams

#include "Game.h"

using namespace std;

Game::Game()
{
    day_time = 0;
    days_since_last_c = 0;
    next_caravan = 0; //increases only when current caravan leaves or dies
}

void Game::readWriteFile()//xxx works but is shitty
{
    
    ifstream myfilestream;
    myfilestream.open("end_result.txt");
    
    if (myfilestream.is_open())
    {
        string line = "";
        getline(myfilestream, line);
        if (stoi(line) < player.getDays_survived())
        {
            cout << "You survived longer this time!" << endl;
        }
        myfilestream.close();
    }
    else
    {
        myfilestream.close();
    }
    
    //filewriting
    ofstream write;
    write.open("end_result.txt");
    
    if (write.is_open())
    {
        write << player.getDays_survived() << endl;
        write << player.getName() << endl;
        
        write.close();
    }
    else
    {
        write.close();
    }
}

//game variables{

void Game::setDay_time(int x)
{
    day_time = x;
}

int Game::getDay_time()
{
    return day_time;
}

void Game::displayDay_time()
{
    switch (getDay_time())
    {
        case 0: //morning 
            cout << "It be the morning of ";
            break;
        case 1: //evening
            cout << "It's the eveninģ̴̣̫͔̲̻̖̜̲͉̹͖͙̐̈ͩ̅̓͛ͩ̌̈́͜͜ of ";
            break;
        case 2: //night
            cout << "ń̬̳̝̤̠̤̘͑̋̏̇i̗̥̲͕͚̽ͯ̏g̫̙̘̼͚̤̓͒ͮ͗́h͚̄t͖̗̣͎̅̊͐̊͘ ͚̬͓̘̇t̡ͬ̍̆͊͊iͯͨͅm̞̜̟̩̺̳̒͛ͫḙ̸͐̍̈̃̎̚ of " ;
            break;
        default: 
            cout << "ERROR: day_time is bugged up: " << getDay_time() << endl;
    }
}

void Game::incrementDay_time()
{
    //reduce wakefulness
    player.setWakefulness( player.getWakefulness() -1 );
    
    if (getDay_time() == 2)//if it's night
    {
        player.setDays_survived( player.getDays_survived() +1 );//new day
        setDay_time(0);//morning now
        inventory.setFood( inventory.getFood() -1 );
        if (caravan[next_caravan].getPresence() == false)
        {
            days_since_last_c += 1;
        }
        
        caravanTime();
    }
    else
    {
        setDay_time( getDay_time() +1 );
    }
}

//days since last caravan
void Game::setDays_since_last_c(int x)
{
    days_since_last_c = x;
}

int Game::getDays_since_last_c()
{
    return days_since_last_c;
}

//next caravan
void Game::setNext_caravan(int x)
{
    next_caravan = x;
}

int Game::getNext_caravan()
{
    return next_caravan;
}

//}  end of game variable functions

//text display functions{
void Game::help()
{
    string x;
    cout << "Right, so you can only do 3 actions a day. " << endl;
    cout << "THe first three options use up time in your day" << endl << endl;
    cout << "1. Observing the trail allows you to interact with any caravans" << endl;
    cout << "that might be traveling or stopping by in the next 1/3 of your day" << endl;
    cout << "2. Hunting in the forest does exactly that. You might encounter an animal or something." << endl;
    cout << "3. Resting in your hideout restores wakefulness and does something other helpful shit i think" << endl;
    cout << "4. Save/Load file is pretty self explanatory" << endl;
    cout << "5. Helpful information will display this stuff again" << endl;
    cout << "99. Quit is also pretty self explanatory. Remember to save first!" << endl << endl;
    cout << "Try not to die. I'm sure that you can figure out what causes death, and how to avoid it" << endl;
    cout << "Understand?" << endl;
    getline(cin, x);
    cout << "I don't care lol. Just press 5 to see this again, or scroll up, nerd" << endl;
}

void Game::introduction()
{
    string x;
    cout << "Welcome to Oregon Trailend!" << endl;
    cout << endl;
    cout << "The year is 1835, and people be traveling to Oregon or something like that. " << endl;
    cout << "Anyway, you are a hermit that has lived in the forest for a long time. " << endl;
    cout << "Now with 50 caravans moving west, your peaceful life is under threat. " << endl;
    cout << "So your goal is to steal, sabotage, do whatever you can to end as many Oregon journeys" << endl;
    cout << "as possible to protect the forest. It's rather convenient that your hideout is close to the trail." << endl;
    cout << "Your infamy level represents the number of caravans you have destroyed." << endl;
    cout << endl;
    cout << "Enter your name to continue: " ;
    getline(cin, x);
    player.setName(x);
    cout << "Cool beans, " << player.getName() << endl << endl;
    help();
    cout << endl;
}

void Game::playerStats()
{
    cout << "Day " << player.getDays_survived() << endl;
    cout << "Health: " << player.getHealth() << "     ";
    cout << "Infamy: " << player.getInfamy() << "     ";
    cout << "Wakefulness: " << player.getWakefulness() << endl;
}

void Game::inventoryStats()
{
    cout << "Coins: " << inventory.getCoins() << "     ";
    cout << "Food: " << inventory.getFood() << "     ";
    cout << "Animal...parts: " << inventory.getAnimal_parts() << "     ";
    cout << "General supplies: " << inventory.getGeneral_supplies() << "     ";
    cout << "Weaponry i think: " << inventory.getWeaponry() << "     " << endl;
}

void Game::allStats()
{
    playerStats();
    inventoryStats();
}

bool Game::caravanCheck()
{
    //making sure there ain't no index out of bounds shit
    //return false immediately
    if (next_caravan == 50)
    {
        return false;
    }
    //caravan is already on the trail
    if (caravan[next_caravan].getPresence() == true)
    {
        return true;
    }
    //remember that this is checked every day_time tick
    int random_number;
    switch (days_since_last_c)
    {
        case 0: //0% chance
            return false;
            break;
        case 1: //5%
            random_number = (rand() % 5); //generates random numbers 0-4
            if (random_number < 1) 
            {
                caravan[next_caravan].setPresence(true);
                days_since_last_c = 0; //reset it!
                return true;
            }
            else return false;
            break;
        case 2: //10%
            random_number = (rand() % 10); //generates random numbers 0-9
            if (random_number < 1) 
            {
                caravan[next_caravan].setPresence(true);
                days_since_last_c = 0; //reset it!
                return true;
            }
            else return false;
            break;
        case 3: //15%
            random_number = (rand() % 99); //generates random numbers 0-9
            if (random_number < 15) 
            {
                caravan[next_caravan].setPresence(true);
                days_since_last_c = 0; //reset it!
                return true;
            }
            else return false;
            break;
        case 4: //20%
            random_number = (rand() % 10); //generates random numbers 0-9
            if (random_number < 2) 
            {
                caravan[next_caravan].setPresence(true);
                days_since_last_c = 0; //reset it!
                return true;
            }
            else return false;
            break;
        case 5: //25%
            random_number = (rand() % 100); //generates random numbers 0-99
            if (random_number < 25) 
            {
                caravan[next_caravan].setPresence(true);
                days_since_last_c = 0; //reset it!
                return true;
            }
            else return false;
            break;
        case 6: //30%
            random_number = (rand() % 10); //generates random numbers 0-9
            if (random_number < 3) 
            {
                caravan[next_caravan].setPresence(true);
                days_since_last_c = 0; //reset it!
                return true;
            }
            else return false;
            break;
        default: //40% for 7+ days_since_last_c
            random_number = (rand() % 10); //generates random numbers 0-9
            if (random_number < 4) 
            {
                caravan[next_caravan].setPresence(true);
                days_since_last_c = 0; //reset it!
                return true;
            }
            else return false;
    }//end of switch statement
    
    
}

void Game::mainMenu()
{
    displayDay_time();
    allStats();
    
    cout << endl; 
    
    if (caravan[next_caravan].getPresence() == true)
    {
        cout << "1. Caravan " << next_caravan << " is on the trail..." << endl;
    }
    else
    {
        cout << "Nothing on the trail..." << endl;
    }
    
    cout << "2. Hunt in the forest" << endl;
    cout << "3. Rest in hideout" << endl;
    cout << "4. Save/Load file" << endl;
    cout << "5. Helpful information" << endl;
    cout << "99. Quit" << endl;
}

bool Game::death()
{
    if (player.getHealth() <= 0)
    {
        cout << "You didn't feel so good and vanished into dust." << endl;
        cout << "RIP " << player.getName() << endl;
        cout << "You survived " << player.getDays_survived() << " days and ended " << player.getInfamy() << " / 50 caravans" << endl;
        return true; // player died
    }
    else if (player.getWakefulness() < 0)
    {
        cout << "You were so tired, you fell asleep and didn't wake back up again. Whoops." << endl;
        cout << "RIP " << player.getName() << endl;
        cout << "You survived " << player.getDays_survived() << " days and ended " << player.getInfamy() << " / 50 caravans" << endl;
        return true;
    }
    else if (inventory.getFood() < 0)
    {
        cout << "You ran out of food and ate yourself out of hunger. Now did you become twice as big, or did you disappear altogether?" << endl;
        cout << "RIP " << player.getName() << endl;
        cout << "You survived " << player.getDays_survived() << " days and ended " << player.getInfamy() << " / 50 caravans" << endl;
        return true;
    }
    else
    {
        return false;
    }
}

void Game::caravanStats()
{
    cout << "Caravan " << next_caravan << " stats:" << endl;
    
    cout << "Wagons: " << caravan[next_caravan].getWagons() << "     ";
    cout << "Oxen: " << caravan[next_caravan].getOxen() << "     ";
    cout << "People: " << caravan[next_caravan].getPeople() << endl;
    
    if (caravan[next_caravan].getPlayer_spy() == true)
    {
        cout << "Food: " << caravan[next_caravan].getC_food() << "     ";
        cout << "Coins: " << caravan[next_caravan].getC_coins() << "     ";
        cout << "Animal parts: " << caravan[next_caravan].getC_animal_parts() << "     ";
        cout << "General supplies: " << caravan[next_caravan].getC_general_supplies() << "     ";
        cout << "Weaponry: " << caravan[next_caravan].getC_weaponry() << endl;
    }
    else
    {
        cout << "You have not spied on caravan " << next_caravan << " yet." << endl;
        cout << "Food: ?    ";
        cout << "Coins: ?    ";
        cout << "Animal parts: ?    ";
        cout << "General supplies: ?    ";
        cout << "Weaponry: ?" << endl << endl;
    }
    
    if (caravan[next_caravan].getPlayer_perception() == true)
    {
        cout << "They know something spooky is here, and are very vigilant. " << endl;
    }
    cout << "Time to cause some mayhem..." << endl;
}

void Game::caravanInteractions()
{
    cout << "1. Steal" << endl; //has another choice layer
    cout << "2. Sabotage: uses 3 of all your supplies, except food" << endl;
    cout << "3. Assassinate: uses 3 weaponry" << endl;
    cout << "4. Never mind, I don't want to do anything to them currently" << endl;
}
void Game::caravanMenu()
{
    caravanStats();
    caravanInteractions();
}
//}

void Game::caravanTime()
{
    if ( caravan[next_caravan].getPresence() == true)
    {
        
        //food subtraction & people starvation, if any
        int food_diff = caravan[next_caravan].getC_food() - caravan[next_caravan].getPeople();
        if (food_diff >= 0 )
        {
            caravan[next_caravan].setC_food( food_diff );
        }
        else
        {
            caravan[next_caravan].setC_food(0);
            caravan[next_caravan].setPeople( caravan[next_caravan].getPeople() + food_diff);
            cout << -1 * food_diff << " people in caravan " << next_caravan << " starved to death." << endl;
        }
        
        //recalculate mobility
        caravan[next_caravan].setMobility( caravan[next_caravan].calcMobility());
        
        if (caravan[next_caravan].getMobility() == false && 
            caravan[next_caravan].getC_general_supplies() >= 3 &&
            caravan[next_caravan].getPeople() > 0)
        {
            caravan[next_caravan].setC_general_supplies( caravan[next_caravan].getC_general_supplies() -3);
            cout << "Caravan " << next_caravan << " made a wagon using their general supplies" << endl;
        }
        
        //recalculate mobility
        caravan[next_caravan].setMobility( caravan[next_caravan].calcMobility());
        
        if (caravan[next_caravan].getMobility() == true)
        {
            if (caravan[next_caravan].getPlayer_perception() == true)
            {
                cout << "Caravan " << next_caravan << " continued their journey on the trail." << endl;
                next_caravan++;
            }
            else if ((rand() % 100) < 50)
            {
                cout << "Caravan " << next_caravan << " continued their journey on the trail." << endl;
                next_caravan++;
            }
        }
        
        //recalculate mobility
        caravan[next_caravan].setMobility( caravan[next_caravan].calcMobility() );
        caravanDeath();
    }
}

void Game::caravanDeath()
{
    bool death = false;
    if (caravan[next_caravan].getPeople() == 0)
    {
        death = true;
    }
    else if (caravan[next_caravan].getSurvival() <= 0)
    {
        death = true;
    }
    if (death == true)
    { 
        caravan[next_caravan].setPresence(false);
        cout << "Caravan " << next_caravan << " failed to survive. " << endl;
        cout << "Their leftover supplies are yours to take... " << endl;
        
        inventory.setFood( inventory.getFood() + caravan[next_caravan].getC_food() + caravan[next_caravan].getOxen() );
        inventory.setCoins( inventory.getCoins() + caravan[next_caravan].getC_coins() );
        inventory.setAnimal_parts(inventory.getAnimal_parts() + caravan[next_caravan].getC_animal_parts() + caravan[next_caravan].getOxen());
        inventory.setGeneral_supplies( inventory.getGeneral_supplies() + caravan[next_caravan].getC_general_supplies() + caravan[next_caravan].getWagons()); 
        inventory.setWeaponry( inventory.getWeaponry() + caravan[next_caravan].getC_weaponry() );
        player.setInfamy(player.getInfamy() + 1); //increment caravan kill count
        
        next_caravan++;
    }
}

//stealing shit: 90% of this is copy pasted cuz i didn't figure
//out an elegant way to use functions lmao

void Game::stealOptions()
{
    cout << "What to steal?" << endl;
    cout << "1. Food" << endl;
    cout << "2. Coins" << endl;
    cout << "3. Animal bits" << endl;
    cout << "4. General supplies" << endl;
    cout << "5. Weaponry" << endl;
    cout << "6. Never mind hehexd" << endl;
}
void Game::stealFood()
{
    int rng = (rand() % 100); //generates random numbers 0-99

    int amount = (3 + rand() % 3); //3-5
    if (amount > caravan[next_caravan].getC_food())//capping steal amount to prevent negative numbers
    {
        amount = caravan[next_caravan].getC_food();
    }
    
    if (caravan[next_caravan].getPlayer_perception() == false && day_time == 2)//night
    {
        if (rng < 90)//90% success
        {
            cout << "Naisu. Thievery successful." << endl;
            cout << "Stole " << amount << " of their daily rations" << endl;
            caravan[next_caravan].setC_food(caravan[next_caravan].getC_food() - amount);
            inventory.setFood(inventory.getFood() + amount);
            caravan[next_caravan].setPlayer_spy(true);
            
            if ((rand() % 4) == 0)
            {
                cout << "You were detected, but got away safely" << endl;
                caravan[next_caravan].setPlayer_perception(true);
            }
            else
            {
                cout << "You evaded detection" << endl;
            }
        }
        else
        {
            cout << "You were detected and promptly attacked" << endl;
            caravan[next_caravan].setPlayer_perception(true);
            player.setHealth(player.getHealth() - (5 + caravan[next_caravan].getC_weaponry() * 3));
            cout << "Took " << (5 + caravan[next_caravan].getC_weaponry() * 3) << " damage" << endl;
        }
    }
    else if (caravan[next_caravan].getPlayer_perception() == false && day_time != 2)//not night
    {
        if (rng < 80)//80% success
        {
            cout << "Naisu. Thievery successful." << endl;
            cout << "Stole " << amount << " of their daily rations" << endl;
            caravan[next_caravan].setC_food(caravan[next_caravan].getC_food() - amount);
            inventory.setFood(inventory.getFood() + amount);
            caravan[next_caravan].setPlayer_spy(true);
            
            if ((rand() % 4) == 0)
            {
                cout << "You were detected, but got away safely" << endl;
                caravan[next_caravan].setPlayer_perception(true);
            }
            else
            {
                cout << "You evaded detection" << endl;
            }
        }
        else
        {
            cout << "You were detected and promptly attacked" << endl;
            caravan[next_caravan].setPlayer_perception(true);
            player.setHealth(player.getHealth() - (5 + caravan[next_caravan].getC_weaponry() * 3));
            cout << "Took " << (5 + caravan[next_caravan].getC_weaponry() * 3) << " damage" << endl;
        }
    }
    else if (caravan[next_caravan].getPlayer_perception() == true && day_time == 2)//night
    {
        if (rng < 50)//50% success
        {
            cout << "Naisu. Thievery successful." << endl;
            cout << "Stole " << amount << " of their daily rations" << endl;
            caravan[next_caravan].setC_food(caravan[next_caravan].getC_food() - amount);
            inventory.setFood(inventory.getFood() + amount);
            caravan[next_caravan].setPlayer_spy(true);
        }
        else
        {
            cout << "You were detected and promptly attacked" << endl;
            caravan[next_caravan].setPlayer_perception(true);
            player.setHealth(player.getHealth() - (5 + caravan[next_caravan].getC_weaponry() * 3));
            cout << "Took " << (5 + caravan[next_caravan].getC_weaponry() * 3) << " damage" << endl;
        }
    }
    else    //player_perception == true && day_time != 2
    {
        if (rng < 40)//40% success
        {
            cout << "Naisu. Thievery successful." << endl;
            cout << "Stole " << amount << " of their daily rations" << endl;
            caravan[next_caravan].setC_food(caravan[next_caravan].getC_food() - amount);
            inventory.setFood(inventory.getFood() + amount);
            caravan[next_caravan].setPlayer_spy(true);
        }
        else
        {
            cout << "You were detected and promptly attacked" << endl;
            caravan[next_caravan].setPlayer_perception(true);
            player.setHealth(player.getHealth() - (5 + caravan[next_caravan].getC_weaponry() * 3));
            cout << "Took " << (5 + caravan[next_caravan].getC_weaponry() * 3) << " damage" << endl;
        }
    }
}
void Game::stealCoins()
{
    int rng = (rand() % 100); //generates random numbers 0-99
    
    int amount = (3 + rand() % 3); //3-5
    if (amount > caravan[next_caravan].getC_coins())//capping steal amount to prevent negative numbers
    {
        amount = caravan[next_caravan].getC_coins();
    }
    
    if (caravan[next_caravan].getPlayer_perception() == false && day_time == 2)//night
    {
        if (rng < 90)//90% success
        {
            cout << "Naisu. Thievery successful." << endl;
            cout << "Stole " << amount << " of their coins" << endl;
            caravan[next_caravan].setC_coins(caravan[next_caravan].getC_coins() - amount);
            inventory.setCoins(inventory.getCoins() + amount);
            caravan[next_caravan].setPlayer_spy(true);
            
            if ((rand() % 4) == 0)
            {
                cout << "You were detected, but got away safely" << endl;
                caravan[next_caravan].setPlayer_perception(true);
            }
            else
            {
                cout << "You evaded detection" << endl;
            }
        }
        else
        {
            cout << "You were detected and promptly attacked" << endl;
            caravan[next_caravan].setPlayer_perception(true);
            player.setHealth(player.getHealth() - (5 + caravan[next_caravan].getC_weaponry() * 3));
            cout << "Took " << (5 + caravan[next_caravan].getC_weaponry() * 3) << " damage" << endl;
        }
    }
    else if (caravan[next_caravan].getPlayer_perception() == false && day_time != 2)//not night
    {
        if (rng < 80)//80% success
        {
            cout << "Naisu. Thievery successful." << endl;
            cout << "Stole " << amount << " of their coins" << endl;
            caravan[next_caravan].setC_coins(caravan[next_caravan].getC_coins() - amount);
            inventory.setCoins(inventory.getCoins() + amount);
            caravan[next_caravan].setPlayer_spy(true);
            
            if ((rand() % 4) == 0)
            {
                cout << "You were detected, but got away safely" << endl;
                caravan[next_caravan].setPlayer_perception(true);
            }
            else
            {
                cout << "You evaded detection" << endl;
            }
        }
        else
        {
            cout << "You were detected and promptly attacked" << endl;
            caravan[next_caravan].setPlayer_perception(true);
            player.setHealth(player.getHealth() - (5 + caravan[next_caravan].getC_weaponry() * 3));
            cout << "Took " << (5 + caravan[next_caravan].getC_weaponry() * 3) << " damage" << endl;
        }
    }
    else if (caravan[next_caravan].getPlayer_perception() == true && day_time == 2)//night
    {
        if (rng < 50)//50% success
        {
            cout << "Naisu. Thievery successful." << endl;
            cout << "Stole " << amount << " of their coins" << endl;
            caravan[next_caravan].setC_coins(caravan[next_caravan].getC_coins() - amount);
            inventory.setCoins(inventory.getCoins() + amount);
            caravan[next_caravan].setPlayer_spy(true);
        }
        else
        {
            cout << "You were detected and promptly attacked" << endl;
            caravan[next_caravan].setPlayer_perception(true);
            player.setHealth(player.getHealth() - (5 + caravan[next_caravan].getC_weaponry() * 3));
            cout << "Took " << (5 + caravan[next_caravan].getC_weaponry() * 3) << " damage" << endl;
        }
    }
    else    //player_perception == true && day_time != 2
    {
        if (rng < 40)//40% success
        {
            cout << "Naisu. Thievery successful." << endl;
            cout << "Stole " << amount << " of their coins" << endl;
            caravan[next_caravan].setC_coins(caravan[next_caravan].getC_coins() - amount);
            inventory.setCoins(inventory.getCoins() + amount);
            caravan[next_caravan].setPlayer_spy(true);
        }
        else
        {
            cout << "You were detected and promptly attacked" << endl;
            caravan[next_caravan].setPlayer_perception(true);
            player.setHealth(player.getHealth() - (5 + caravan[next_caravan].getC_weaponry() * 3));
            cout << "Took " << (5 + caravan[next_caravan].getC_weaponry() * 3) << " damage" << endl;
        }
    }
}
void Game::stealAnimalParts()
{
    int rng = (rand() % 100); //generates random numbers 0-99
    
    int amount = (3 + rand() % 3); //3-5
    if (amount > caravan[next_caravan].getC_animal_parts())//capping steal amount to prevent negative numbers
    {
        amount = caravan[next_caravan].getC_animal_parts();
    }
    
    if (caravan[next_caravan].getPlayer_perception() == false && day_time == 2)//night
    {
        if (rng < 90)//90% success
        {
            cout << "Naisu. Thievery successful." << endl;
            cout << "Stole " << amount << " of their animal parts" << endl;
            caravan[next_caravan].setC_animal_parts(caravan[next_caravan].getC_animal_parts() - amount);
            inventory.setAnimal_parts(inventory.getAnimal_parts() + amount);
            caravan[next_caravan].setPlayer_spy(true);
            
            if ((rand() % 4) == 0)
            {
                cout << "You were detected, but got away safely" << endl;
                caravan[next_caravan].setPlayer_perception(true);
            }
            else
            {
                cout << "You evaded detection" << endl;
            }
        }
        else
        {
            cout << "You were detected and promptly attacked" << endl;
            caravan[next_caravan].setPlayer_perception(true);
            player.setHealth(player.getHealth() - (5 + caravan[next_caravan].getC_weaponry() * 3));
            cout << "Took " << (5 + caravan[next_caravan].getC_weaponry() * 3) << " damage" << endl;
        }
    }
    else if (caravan[next_caravan].getPlayer_perception() == false && day_time != 2)//not night
    {
        if (rng < 80)//80% success
        {
            cout << "Naisu. Thievery successful." << endl;
            cout << "Stole " << amount << " of their animal parts" << endl;
            caravan[next_caravan].setC_animal_parts(caravan[next_caravan].getC_animal_parts() - amount);
            inventory.setAnimal_parts(inventory.getAnimal_parts() + amount);
            caravan[next_caravan].setPlayer_spy(true);
            
            if ((rand() % 4) == 0)
            {
                cout << "You were detected, but got away safely" << endl;
                caravan[next_caravan].setPlayer_perception(true);
            }
            else
            {
                cout << "You evaded detection" << endl;
            }
        }
        else
        {
            cout << "You were detected and promptly attacked" << endl;
            caravan[next_caravan].setPlayer_perception(true);
            player.setHealth(player.getHealth() - (5 + caravan[next_caravan].getC_weaponry() * 3));
            cout << "Took " << (5 + caravan[next_caravan].getC_weaponry() * 3) << " damage" << endl;
        }
    }
    else if (caravan[next_caravan].getPlayer_perception() == true && day_time == 2)//night
    {
        if (rng < 50)//50% success
        {
            cout << "Naisu. Thievery successful." << endl;
            cout << "Stole " << amount << " of their animal parts" << endl;
            caravan[next_caravan].setC_animal_parts(caravan[next_caravan].getC_animal_parts() - amount);
            inventory.setAnimal_parts(inventory.getAnimal_parts() + amount);
            caravan[next_caravan].setPlayer_spy(true);
        }
        else
        {
            cout << "You were detected and promptly attacked" << endl;
            caravan[next_caravan].setPlayer_perception(true);
            player.setHealth(player.getHealth() - (5 + caravan[next_caravan].getC_weaponry() * 3));
            cout << "Took " << (5 + caravan[next_caravan].getC_weaponry() * 3) << " damage" << endl;
        }
    }
    else    //player_perception == true && day_time != 2
    {
        if (rng < 40)//40% success
        {
            cout << "Naisu. Thievery successful." << endl;
            cout << "Stole " << amount << " of their animal parts" << endl;
            caravan[next_caravan].setC_animal_parts(caravan[next_caravan].getC_animal_parts() - amount);
            inventory.setAnimal_parts(inventory.getAnimal_parts() + amount);
            caravan[next_caravan].setPlayer_spy(true);
        }
        else
        {
            cout << "You were detected and promptly attacked" << endl;
            caravan[next_caravan].setPlayer_perception(true);
            player.setHealth(player.getHealth() - (5 + caravan[next_caravan].getC_weaponry() * 3));
            cout << "Took " << (5 + caravan[next_caravan].getC_weaponry() * 3) << " damage" << endl;
        }
    }
}
void Game::stealGeneralSupplies()
{
    int rng = (rand() % 100); //generates random numbers 0-99

    int amount = (3 + rand() % 3); //3-5
    if (amount > caravan[next_caravan].getC_general_supplies())//capping steal amount to prevent negative numbers
    {
        amount = caravan[next_caravan].getC_general_supplies();
    }
    
    if (caravan[next_caravan].getPlayer_perception() == false && day_time == 2)//night
    {
        if (rng < 90)//90% success
        {
            cout << "Naisu. Thievery successful." << endl;
            cout << "Stole " << amount << " of their general supplies" << endl;
            caravan[next_caravan].setC_general_supplies(caravan[next_caravan].getC_general_supplies() - amount);
            inventory.setGeneral_supplies(inventory.getGeneral_supplies() + amount);
            caravan[next_caravan].setPlayer_spy(true);
            
            if ((rand() % 4) == 0)
            {
                cout << "You were detected, but got away safely" << endl;
                caravan[next_caravan].setPlayer_perception(true);
            }
            else
            {
                cout << "You evaded detection" << endl;
            }
        }
        else
        {
            cout << "You were detected and promptly attacked" << endl;
            caravan[next_caravan].setPlayer_perception(true);
            player.setHealth(player.getHealth() - (5 + caravan[next_caravan].getC_weaponry() * 3));
            cout << "Took " << (5 + caravan[next_caravan].getC_weaponry() * 3) << " damage" << endl;
        }
    }
    else if (caravan[next_caravan].getPlayer_perception() == false && day_time != 2)//not night
    {
        if (rng < 80)//80% success
        {
            cout << "Naisu. Thievery successful." << endl;
            cout << "Stole " << amount << " of their general supplies" << endl;
            caravan[next_caravan].setC_general_supplies(caravan[next_caravan].getC_general_supplies() - amount);
            inventory.setGeneral_supplies(inventory.getGeneral_supplies() + amount);
            caravan[next_caravan].setPlayer_spy(true);
            
            if ((rand() % 4) == 0)
            {
                cout << "You were detected, but got away safely" << endl;
                caravan[next_caravan].setPlayer_perception(true);
            }
            else
            {
                cout << "You evaded detection" << endl;
            }
        }
        else
        {
            cout << "You were detected and promptly attacked" << endl;
            caravan[next_caravan].setPlayer_perception(true);
            player.setHealth(player.getHealth() - (5 + caravan[next_caravan].getC_weaponry() * 3));
            cout << "Took " << (5 + caravan[next_caravan].getC_weaponry() * 3) << " damage" << endl;
        }
    }
    else if (caravan[next_caravan].getPlayer_perception() == true && day_time == 2)//night
    {
        if (rng < 50)//50% success
        {
            cout << "Naisu. Thievery successful." << endl;
            cout << "Stole " << amount << " of their general supplies" << endl;
            caravan[next_caravan].setC_general_supplies(caravan[next_caravan].getC_general_supplies() - amount);
            inventory.setGeneral_supplies(inventory.getGeneral_supplies() + amount);
            caravan[next_caravan].setPlayer_spy(true);
        }
        else
        {
            cout << "You were detected and promptly attacked" << endl;
            caravan[next_caravan].setPlayer_perception(true);
            player.setHealth(player.getHealth() - (5 + caravan[next_caravan].getC_weaponry() * 3));
            cout << "Took " << (5 + caravan[next_caravan].getC_weaponry() * 3) << " damage" << endl;
        }
    }
    else    //player_perception == true && day_time != 2
    {
        if (rng < 40)//40% success
        {
            cout << "Naisu. Thievery successful." << endl;
            cout << "Stole " << amount << " of their general supplies" << endl;
            caravan[next_caravan].setC_general_supplies(caravan[next_caravan].getC_general_supplies() - amount);
            inventory.setGeneral_supplies(inventory.getGeneral_supplies() + amount);
            caravan[next_caravan].setPlayer_spy(true);
        }
        else
        {
            cout << "You were detected and promptly attacked" << endl;
            caravan[next_caravan].setPlayer_perception(true);
            player.setHealth(player.getHealth() - (5 + caravan[next_caravan].getC_weaponry() * 3));
            cout << "Took " << (5 + caravan[next_caravan].getC_weaponry() * 3) << " damage" << endl;
        }
    }
}
void Game::stealWeaponry()
{
    int rng = (rand() % 100); //generates random numbers 0-99

    int amount = (3 + rand() % 3); //3-5
    if (amount > caravan[next_caravan].getC_weaponry())//capping steal amount to prevent negative numbers
    {
        amount = caravan[next_caravan].getC_weaponry();
    }
    
    if (caravan[next_caravan].getPlayer_perception() == false && day_time == 2)//night
    {
        if (rng < 90)//90% success
        {
            cout << "Naisu. Thievery successful." << endl;
            cout << "Stole " << amount << " of their weaponry" << endl;
            caravan[next_caravan].setC_weaponry(caravan[next_caravan].getC_weaponry() - amount);
            inventory.setWeaponry(inventory.getWeaponry() + amount);
            caravan[next_caravan].setPlayer_spy(true);
            
            if ((rand() % 4) == 0)
            {
                cout << "You were detected, but got away safely" << endl;
                caravan[next_caravan].setPlayer_perception(true);
            }
            else
            {
                cout << "You evaded detection" << endl;
            }
        }
        else
        {
            cout << "You were detected and promptly attacked" << endl;
            caravan[next_caravan].setPlayer_perception(true);
            player.setHealth(player.getHealth() - (5 + caravan[next_caravan].getC_weaponry() * 3));
            cout << "Took " << (5 + caravan[next_caravan].getC_weaponry() * 3) << " damage" << endl;
        }
    }
    else if (caravan[next_caravan].getPlayer_perception() == false && day_time != 2)//not night
    {
        if (rng < 80)//80% success
        {
            cout << "Naisu. Thievery successful." << endl;
            cout << "Stole " << amount << " of their weaponry" << endl;
            caravan[next_caravan].setC_weaponry(caravan[next_caravan].getC_weaponry() - amount);
            inventory.setWeaponry(inventory.getWeaponry() + amount);
            caravan[next_caravan].setPlayer_spy(true);
            
            if ((rand() % 4) == 0)
            {
                cout << "You were detected, but got away safely" << endl;
                caravan[next_caravan].setPlayer_perception(true);
            }
            else
            {
                cout << "You evaded detection" << endl;
            }
        }
        else
        {
            cout << "You were detected and promptly attacked" << endl;
            caravan[next_caravan].setPlayer_perception(true);
            player.setHealth(player.getHealth() - (5 + caravan[next_caravan].getC_weaponry() * 3));
            cout << "Took " << (5 + caravan[next_caravan].getC_weaponry() * 3) << " damage" << endl;
        }
    }
    else if (caravan[next_caravan].getPlayer_perception() == true && day_time == 2)//night
    {
        if (rng < 50)//50% success
        {
            cout << "Naisu. Thievery successful." << endl;
            cout << "Stole " << amount << " of their weaponry" << endl;
            caravan[next_caravan].setC_weaponry(caravan[next_caravan].getC_weaponry() - amount);
            inventory.setWeaponry(inventory.getWeaponry() + amount);
            caravan[next_caravan].setPlayer_spy(true);
        }
        else
        {
            cout << "You were detected and promptly attacked" << endl;
            caravan[next_caravan].setPlayer_perception(true);
            player.setHealth(player.getHealth() - (5 + caravan[next_caravan].getC_weaponry() * 3));
            cout << "Took " << (5 + caravan[next_caravan].getC_weaponry() * 3) << " damage" << endl;
        }
    }
    else    //player_perception == true && day_time != 2
    {
        if (rng < 40)//40% success
        {
            cout << "Naisu. Thievery successful." << endl;
            cout << "Stole " << amount << " of their weaponry" << endl;
            caravan[next_caravan].setC_weaponry(caravan[next_caravan].getC_weaponry() - amount);
            inventory.setWeaponry(inventory.getWeaponry() + amount);
            caravan[next_caravan].setPlayer_spy(true);
        }
        else
        {
            cout << "You were detected and promptly attacked" << endl;
            caravan[next_caravan].setPlayer_perception(true);
            player.setHealth(player.getHealth() - (5 + caravan[next_caravan].getC_weaponry() * 3));
            cout << "Took " << (5 + caravan[next_caravan].getC_weaponry() * 3) << " damage" << endl;
        }
    }
}


void Game::damage()
{
    cout << "Sabotage successful." << endl;
    
    caravan[next_caravan].setPlayer_spy(true);
    
    //damage initalization{
    int d_wagons = (rand() % 2); //0-1
    int d_oxen = (rand() % 2); //0-1
    int d_food = (5+ rand() % 11); //5-15
    int d_coins = (5+ rand() % 6); //5-10
    int d_general_supplies = (5+ rand() % 6); //5-10
    int d_animal_parts = (5+ rand() % 6); //5-10
    int d_weaponry = (5+ rand() % 6); //5-10
    //}
    
    //damage capping{
    if (d_wagons > caravan[next_caravan].getWagons())
    {
        d_wagons = caravan[next_caravan].getWagons();
    }
    if (d_oxen > caravan[next_caravan].getOxen())
    {
        d_oxen = caravan[next_caravan].getOxen();
    }
    if (d_food > caravan[next_caravan].getC_food())
    {
        d_food = caravan[next_caravan].getC_food();
    }
    if (d_coins > caravan[next_caravan].getC_coins())
    {
        d_coins = caravan[next_caravan].getC_coins();
    }
    if (d_general_supplies > caravan[next_caravan].getC_general_supplies())
    {
        d_general_supplies = caravan[next_caravan].getC_general_supplies();
    }
    if (d_animal_parts > caravan[next_caravan].getC_animal_parts())
    {
        d_animal_parts = caravan[next_caravan].getC_animal_parts();
    }
    if (d_weaponry > caravan[next_caravan].getC_weaponry())
    {
        d_weaponry = caravan[next_caravan].getC_weaponry();
    }
    //}
    
    //dealing damage{
    caravan[next_caravan].setWagons( caravan[next_caravan].getWagons() - d_wagons);
    caravan[next_caravan].setOxen( caravan[next_caravan].getOxen() - d_oxen);
    caravan[next_caravan].setC_food( caravan[next_caravan].getC_food() - d_food);
    caravan[next_caravan].setC_coins( caravan[next_caravan].getC_coins() - d_coins);
    caravan[next_caravan].setC_general_supplies( caravan[next_caravan].getC_general_supplies() - d_general_supplies);
    caravan[next_caravan].setC_animal_parts( caravan[next_caravan].getC_animal_parts() - d_animal_parts);
    caravan[next_caravan].setC_weaponry( caravan[next_caravan].getC_weaponry() - d_weaponry);
    //}
    
    //printing damage{
    cout << "Destroyed " ;
    cout << d_wagons << " wagons, ";
    cout << d_oxen << " oxen, ";
    cout << d_food << " food, ";
    cout << d_coins << " coins, ";
    cout << d_general_supplies << " general_supplies, ";
    cout << d_animal_parts << " animal_parts, and ";
    cout << d_weaponry << " weaponry in a fire." << endl;
    //}
    
}

void Game::sabotage()
{
    int rng = (rand() % 100); //generates random numbers 0-99
    if (caravan[next_caravan].getPlayer_perception() == false)
    {
        if (day_time == 2)//nighttime
        {
            //80% success, chance of them noticing, player perception = true
            if (rng < 80)
            {
                damage();
                if (rng % 2 == 0) 
                {
                    cout << "They noticed you, but you got away safely" << endl;
                    caravan[next_caravan].setPlayer_perception(true);
                }
                else 
                {
                    cout << "You got away without detection. They thought it was all an accident. Suckers." << endl;
                }
            }
            else //20% unsuccessful
            {
                cout << "Sabotage unsuccessful. They noticed and attacked you" << endl;
                caravan[next_caravan].setPlayer_perception(true);
                player.setHealth(player.getHealth() - (5 + caravan[next_caravan].getC_weaponry() * 3));
                cout << "Took " << (5 + caravan[next_caravan].getC_weaponry() * 3) << " damage" << endl;
            }
        }
        else//not night
        {
            //60% success
            if (rng < 60)
            {
                damage();
                if (rng % 2 == 0) 
                {
                    cout << "They noticed you, but you got away safely" << endl;
                    caravan[next_caravan].setPlayer_perception(true);
                }
                else 
                {
                    cout << "You got away without detection. They thought it was all an accident. Suckers." << endl;
                    caravan[next_caravan].setPlayer_perception(false);
                }
            }
            else //40% unsuccessful
            {
                cout << "Sabotage unsuccessful. They noticed and attacked you" << endl;
                caravan[next_caravan].setPlayer_perception(true);
                player.setHealth(player.getHealth() - (5 + caravan[next_caravan].getC_weaponry() * 3));
                cout << "Took " << (5 + caravan[next_caravan].getC_weaponry() * 3) << " damage" << endl;
            }
        }
    }
    else //they know player is here
    {
        if (day_time == 2)//nighttime
        {
            //60% success
            if (rng < 60)
            {
                damage();
                
            }
            else //40% unsuccessful
            {
                cout << "Sabotage unsuccessful. They noticed and attacked you" << endl;
                caravan[next_caravan].setPlayer_perception(true);//should already be true, but just in case
                player.setHealth(player.getHealth() - (5 + caravan[next_caravan].getC_weaponry() * 3));
                cout << "Took " << (5 + caravan[next_caravan].getC_weaponry() * 3) << " damage" << endl;
            }
            
        }
        else//not night
        {
            //40% success
            if (rng < 40)
            {
                damage();
            }
            else //60% unsuccessful
            {
                cout << "Sabotage unsuccessful. They noticed and attacked you" << endl;
                caravan[next_caravan].setPlayer_perception(true);//should already be true, but just in case
                player.setHealth(player.getHealth() - (5 + caravan[next_caravan].getC_weaponry() * 3));
                cout << "Took " << (5 + caravan[next_caravan].getC_weaponry() * 3) << " damage" << endl;
            }
            
        }
    }
}
bool Game::s_resourceCheck()
{
    if (inventory.getCoins() >= 3 && 
        inventory.getAnimal_parts() >= 3 && 
        inventory.getGeneral_supplies() >= 3 &&
        inventory.getWeaponry() >= 3)
    {
        inventory.setCoins( inventory.getCoins() -3);
        inventory.setAnimal_parts ( inventory.getAnimal_parts() -3);
        inventory.setGeneral_supplies( inventory.getGeneral_supplies() -3);
        inventory.setWeaponry( inventory.getWeaponry() -3);
        return true;
    }
    else return false;
}

bool Game::a_resourceCheck()
{
    if (inventory.getWeaponry() >= 3)
    {
        inventory.setWeaponry( inventory.getWeaponry() -3);
        return true;
    }
    else return false;
}

void Game::assassinate()
{
    int rng = (rand() % 100); //generates random numbers 0-99
    int killcount = (1 + rand() % 3); //1-3
    if (caravan[next_caravan].getPeople() < killcount)
    {
        killcount = caravan[next_caravan].getPeople();
    }
    if (caravan[next_caravan].getPlayer_perception() == false)
    {
        if (day_time == 2)//nighttime
        {
            //90% success
            if (rng < 90)
            {
                cout << "A true creature of the night. Eliminated " << killcount << " fools" << endl;
                caravan[next_caravan].setPeople( caravan[next_caravan].getPeople() - killcount);
                caravan[next_caravan].setPlayer_perception(true);
                caravan[next_caravan].setPlayer_spy(true);
                
            }
            else //10% unsuccessful
            {
                cout << "Assassination unsuccessful. They noticed and attacked you" << endl;
                caravan[next_caravan].setPlayer_perception(true);
                player.setHealth(player.getHealth() - (5 + caravan[next_caravan].getC_weaponry() * 3));
                cout << "Took " << (5 + caravan[next_caravan].getC_weaponry() * 3) << " damage" << endl;
            }
        }
        else//not night
        {
            //70% success
            if (rng < 70)
            {
                cout << "A true creature of the night. Eliminated " << killcount << " fools" << endl;
                caravan[next_caravan].setPeople( caravan[next_caravan].getPeople() - killcount);
                caravan[next_caravan].setPlayer_perception(true);
                caravan[next_caravan].setPlayer_spy(true);
            }
            else //30% unsuccessful
            {
                cout << "Assassination unsuccessful. They noticed and attacked you" << endl;
                caravan[next_caravan].setPlayer_perception(true);
                player.setHealth(player.getHealth() - (5 + caravan[next_caravan].getC_weaponry() * 3));
                cout << "Took " << (5 + caravan[next_caravan].getC_weaponry() * 3) << " damage" << endl;
            }
        }
    }
    else //they know player is here
    {
        if (day_time == 2)//nighttime
        {
            //60% success
            if (rng < 60)
            {
                cout << "A true creature of the night. Eliminated " << killcount << " fools" << endl;
                caravan[next_caravan].setPeople( caravan[next_caravan].getPeople() - killcount);
                caravan[next_caravan].setPlayer_perception(true);
                caravan[next_caravan].setPlayer_spy(true);
                
            }
            else //40% unsuccessful
            {
                cout << "Assassination unsuccessful. They noticed and attacked you" << endl;
                caravan[next_caravan].setPlayer_perception(true);
                player.setHealth(player.getHealth() - (5 + caravan[next_caravan].getC_weaponry() * 3));
                cout << "Took " << (5 + caravan[next_caravan].getC_weaponry() * 3) << " damage" << endl;
            }
            
        }
        else//not night
        {
            //40% success
            if (rng < 40)
            {
                cout << "A true creature of the night. Eliminated " << killcount << " fools" << endl;
                caravan[next_caravan].setPeople( caravan[next_caravan].getPeople() - killcount);
                caravan[next_caravan].setPlayer_perception(true);
                caravan[next_caravan].setPlayer_spy(true);
            }
            else //60% unsuccessful
            {
                cout << "Assassination unsuccessful. They noticed and attacked you" << endl;
                caravan[next_caravan].setPlayer_perception(true);
                player.setHealth(player.getHealth() - (5 + caravan[next_caravan].getC_weaponry() * 3));
                cout << "Took " << (5 + caravan[next_caravan].getC_weaponry() * 3) << " damage" << endl;
            }
            
        }
    }
}

void Game::hunt()
{
    int r = (rand() % 100); //random int 0-99
    int r2 = (rand() % 100); //injury chance
    int increase;
    if (r < 20)//20% chance of success, small creature
    {
        cout << "Hooray, hunted a smol creature" << endl;
        
        increase = (1 + rand() % 2); //generates random numbers 1-2
        inventory.setFood( inventory.getFood() + increase);
        cout << "+" << increase << " food" << endl;
        
        increase = (1 + rand() % 2); //recalculate increase
        inventory.setAnimal_parts( inventory.getAnimal_parts() + increase);
        cout << "+" << increase << " animal...parts" << endl;
    }
    else if (r < 25)//5% success, medium creature
    {
        cout << "Yaw yeET, hunted a medium creature" << endl;
        
        increase = (2 + rand() % 3); //3-5
        inventory.setFood( inventory.getFood() + increase);
        cout << "+" << increase << " food" << endl;
        
        increase = (2 + rand() % 3); //3-5
        inventory.setAnimal_parts( inventory.getAnimal_parts() + increase);
        cout << "+" << increase << " animal...parts" << endl;
        
        if (r2 < (10 - inventory.getWeaponry())) //(10% - weaponry) chance of injury
        {
            increase = (5 + rand() % 5);//5-10
            player.setHealth( player.getHealth() - increase);
            cout << "Unlucky, got bitten and took " << increase << " damage" << endl;
        }
    }
    else if (r < 30)//5% success, thicc creature 
    {
        cout << "cool beans, yoted a thicc creature" << endl;
        
        increase = (4 + rand() % 5); //4-9
        inventory.setFood( inventory.getFood() + increase);
        cout << "+" << increase << " food" << endl;
        
        increase = (4 + rand() % 5); //4-9
        inventory.setAnimal_parts( inventory.getAnimal_parts() + increase);
        cout << "+" << increase << " animal...parts" << endl;
        
        if (r2 < (20 - inventory.getWeaponry()))// (20% - weaponry) chance of injury 
        {
            increase = (10 + rand() % 5);//10-15
            player.setHealth( player.getHealth() - increase);
            cout << "Thicc boi didn't go down without a fight. Took " << increase << " damage" << endl;
        }
    }
    else//didn't hunt anything, 65% chance
    {
        cout << "Nothing found..." << endl;
    }
}

//rest mechanics------------------------
void Game::rest()//recovers +3 wakefulness up to max of 5. Heals +1
{//Rest uses up one wakefulness though, so +2 total
    if (player.getWakefulness() < 5)
    {
        cout << "Rest obtained" << endl;
    }
    
    player.setWakefulness( player.getWakefulness() + 3 );
    if (player.getWakefulness() > 5)
    {
        player.setWakefulness(5);
    }
    
    //heal +2
    if (player.getHealth() < 100)
    {
        player.setHealth( player.getHealth() + (1 + rand() % 2) );//+1-2 health
        cout << "Restored a little health" << endl;
    }
    if (player.getHealth() > 100)//caps health at 100
    {
        player.setHealth(100);
    }
}


void Game::createAllCaravan()
{
    for (int i = 0; i < 15; i++)
    {
        caravan[i].createEasyCaravan();
    }
    for (int i = 15; i < 30; i++)
    {
        caravan[i].createMediumCaravan();
    }
    for (int i = 30; i < 50; i++)
    {
        caravan[i].createHardCaravan();
    }
}

void Game::printAllCaravan()
{
    for (int i = 0; i < 50; i++)
    {
        cout << "Caravan:    " << i << endl;
        cout << "Wagons:     " << caravan[i].getWagons() << endl;
        cout << "Oxen:       " << caravan[i].getOxen() << endl;
        cout << "People:     " << caravan[i].getPeople() << endl;
        cout << "PP:         " << caravan[i].getPlayer_perception() << endl;
        cout << "C_food:     " << caravan[i].getC_food() << endl;
        cout << "C_coins:    " << caravan[i].getC_coins() << endl;
        cout << "C_animal:   " << caravan[i].getC_animal_parts() << endl;
        cout << "C_gen_sup:  " << caravan[i].getC_general_supplies() << endl;
        cout << "C_weaponry: " << caravan[i].getC_weaponry() << endl;
        cout << "Mobility:   " << caravan[i].getMobility() << endl;
        cout << "Survival:   " << caravan[i].getSurvival() << endl;
        cout << "Presence:   " << caravan[i].getPresence() << endl;
        cout << endl;
    }
}

void Game::printCaravanIndex(int x)
{
    cout << "Caravan " << x << endl;
    cout << "Wagons: " << caravan[x].getWagons() << endl;
    cout << "Oxen:   " << caravan[x].getOxen() << endl;
    cout << "People: " << caravan[x].getPeople() << endl;
    cout << "PP:     " << caravan[x].getPlayer_perception() << endl;
    cout << "C_food: " << caravan[x].getC_food() << endl;
    cout << "C_coins: " << caravan[x].getC_coins() << endl;
    cout << "C_animal:   " << caravan[x].getC_animal_parts() << endl;
    cout << "C_gen_sup:  " << caravan[x].getC_general_supplies() << endl;
    cout << "C_weaponry: " << caravan[x].getC_weaponry() << endl;
    cout << "Mobility:   " << caravan[x].getMobility() << endl;
    cout << "Survival:   " << caravan[x].getSurvival() << endl;
    cout << "Presence:   " << caravan[x].getPresence() << endl;
    cout << endl;
}
