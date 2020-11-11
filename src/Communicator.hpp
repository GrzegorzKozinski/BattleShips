#pragma once
#include <iostream>
#include <vector>
#include <memory>

#include "Board.cpp"
#include "Ship.cpp"
using namespace BattleShips;
namespace BattleShips
{
class Communicator
{
private:
   
public:
    Communicator();
    ~Communicator();

    std::pair<char, int> strToPair(std::string str);

    void shipPlacementGuide(std::vector<Ship>& ships);
   
};

std::pair<char, int> strToPair(std::string str)
{
    std::pair<char, int> pair(str.at(0), str.at(1));

    return pair;
}

Communicator::Communicator()
{
    std::cout << "Communicator created!\n";
}

Communicator::~Communicator()
{
    std::cout << "Communicator destroyed!\n";
}

void Communicator::shipPlacementGuide(std::vector<Ship>& ships)
{
    std::string input;
   /*
    do
    {
        shipOrientation.clear();
        std::cout << "Please choose orientation of your ship (h)orizontal / (v)ertical:\n";
        std::getline(std::cin, shipOrientation);

        if(shipOrientation != "h" || shipOrientation != "v") std::cout << "Invalid input!";
    }while(shipOrientation != "h" || shipOrientation != "v");
    */
    
    // podaj pierwsze pole dopoki nie bedzie puste, wytypuj nastepne potencjalne pola,
    // podaj drugie dopoki nie będzie porpawne, 
    // wytypuj nast, podaj kolejne dopoki nie będzie porpawne

    std::set<std::pair<char, int>> coords_tmp;
    
    for (int i = 0; i < 3; ++i) //3 = SHIP_CONST
    {
            
        std::cout << "Choose "<< i+1 << "field of your ship:\n ";
        std::getline(std::cin, input);
        coords_tmp.insert(strToPair(input));
                            

    }
    ships.emplace_back(coords_tmp);

    
}

} // namespace BattleShips