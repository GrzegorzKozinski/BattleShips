#pragma once

#include <iostream>
#include <vector>
#include <memory>
#include <algorithm>

#include "Board.hpp"
#include "Ship.hpp"

namespace BattleShips
{
class Communicator
{
private:
   
public:
    Communicator();
    ~Communicator();

    std::pair<char, int> strToPair(std::string str);
    bool isTaken(std::set<Ship>& ships, const std::pair<char, int>& input) const;
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

bool Communicator::isTaken(std::set<Ship>& ships, const std::pair<char, int>& input) const
{
    
    std::set<std::pair<char, int>>::iterator it;
    for(const auto& ship : ships)
    {
    

        it = std::find(ship.getCoords().begin(), ship.getCoords().end(), input);
        std::cout << "------------Breaks here? " << input.first<<input.second << " a4665465dded\n";
        if(it != ship.getCoords().end()) //found
        { 
          return true;
        }
    }
    return false;
}


void Communicator::shipPlacementGuide(std::set<Ship>& ships)
{   
    std::string input;
   
    std::set<std::pair<char, int>> coords_tmp;
    int i = 0;
    bool fieldTaken;
    
   
    do
    {
        
        std::cout << "Choose field of your ship:\n ";
        std::getline(std::cin, input);
       
        fieldTaken = isTaken(ships, strToPair(input));
        
        if(fieldTaken == false)
        {
            coords_tmp.insert(strToPair(input));
            std::cout << "Field " << input << " added\n";
            ++i;
        }
        else
        {
            std::cout << "invalid input\n";
        }
        
        
    std::cout << " i = " << i;
    }while(i<3);
    ships.emplace(coords_tmp);

    


    
}

} // namespace BattleShips