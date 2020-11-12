#pragma once
#include <iostream>
#include <vector>
#include <memory>
#include <algorithm>

#include "Board.hpp"
#include "Ship.hpp"
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
    bool isTaken(const std::set<Ship>& ships, const std::string& input) const;
    void shipPlacementGuide(std::set<Ship>& ships);
   
};

std::pair<char, int> Communicator::strToPair(std::string str)
{
    std::pair<char, int> p(str.at(0), str.at(1)-48);
  
    return p;
}

Communicator::Communicator()
{
    std::cout << "Communicator created!\n";
}

Communicator::~Communicator()
{
    std::cout << "Communicator destroyed!\n";
}

bool Communicator::isTaken(const std::set<Ship>& ships, const std::string& input) const
{
    bool isFieldTaken = false;
    std::set<std::pair<char, int>>::iterator it;
    for(const auto& ship : ships)
    {

        it = std::find(ship.getCoords().begin(), ship.getCoords().end(), strToPair(input));

        if(it != ship.getCoords().end()) //found
        { 
            fieldTaken == true;
        }
    }
    return isFieldTaken;
}


void Communicator::shipPlacementGuide(std::set<Ship>& ships)
{   
    std::string input;
   
    std::set<std::pair<char, int>> coords_tmp;
    int i = 0;
    bool fieldTaken = isTaken(ships);
    
   
    do
    {
        //possible_moves = getPossibleFields(ships);
        
        std::cout << "Choose field of your ship:\n ";
        std::getline(std::cin, input);

        fieldTaken = isTaken(ships);

        if(fieldTaken == false)
        {
            coords_tmp.insert(strToPair(input));
            std::cout << "Field " << input << " added\n";
            ++i;
        }
        
        
      
    }while(i<3);
    ships.insert(coords_tmp);

    
}

} // namespace BattleShips