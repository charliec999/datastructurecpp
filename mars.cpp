#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>
#include <ctime>


void displayResources(int food, int water, int oxygen);
bool checkGameOver(int food, int water, int oxygen);
void explore(std::string& location, int& food, int& water, int& oxygen);
void gatherResources(int& food, int& water, int& oxygen);

int main() {
    
    std::srand(static_cast<unsigned>(std::time(0)));

    
    int food = 100;     
    int water = 100;    
    int oxygen = 100;   
    std::string location = "Mars Base"; 

    std::cout << "Welcome to the Mars Simulation Game!" << std::endl;

    
    while (true) {
        displayResources(food, water, oxygen);

        
        if (checkGameOver(food, water, oxygen)) {
            break;
        }

        std::cout << "You are currently at: " << location << std::endl;
        std::cout << "What would you like to do? (explore/gather/quit): ";
        std::string action;
        std::cin >> action;

        if (action == "explore") {
            explore(location, food, water, oxygen);
        } else if (action == "gather") {
            gatherResources(food, water, oxygen);
        } else if (action == "quit") {
            std::cout << "Thank you for playing! Goodbye!" << std::endl;
            break;
        } else {
            std::cout << "Invalid action! Please choose explore, gather, or quit." << std::endl;
        }
    }

    return 0;
}


void displayResources(int food, int water, int oxygen) {
    std::cout << "Resources: " << std::endl;
    std::cout << "Food: " << food << std::endl;
    std::cout << "Water: " << water << std::endl;
    std::cout << "Oxygen: " << oxygen << std::endl;
}


bool checkGameOver(int food, int water, int oxygen) {
    if (food <= 0 || water <= 0 || oxygen <= 0) {
        std::cout << "Game Over! You have run out of resources." << std::endl;
        return true;
    }
    return false;
}


void explore(std::string& location, int& food, int& water, int& oxygen) {
    std::cout << "You are exploring Mars..." << std::endl;
    
    if (std::rand() % 2 == 0) {
        location = "Mars Canyon";
        std::cout << "You found a Mars Canyon!" << std::endl;
    } else {
        location = "Mars Mountain";
        std::cout << "You discovered a Mars Mountain!" << std::endl;
    }
    
    food -= 10;
    water -= 5;
    oxygen -= 15;
}


void gatherResources(int& food, int& water, int& oxygen) {
    std::cout << "Gathering resources..." << std::endl;
    int foodGathered = std::rand() % 20 + 1;  
    int waterGathered = std::rand() % 10 + 1; 
    int oxygenGathered = std::rand() % 5 + 1; 

    food += foodGathered;
    water += waterGathered;
    oxygen += oxygenGathered;

    std::cout << "You gathered: " << foodGathered << " food, "
              << waterGathered << " water, and "
              << oxygenGathered << " oxygen." << std::endl;
}
