#pragma once
#include <iostream>
#include <vector>
#include <memory>

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

    void shipPlacementGuide(std::vector<Ship>& ships);
   
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

void Communicator::shipPlacementGuide(std::vector<Ship>& ships)
{
    std::string input;
  
    std::set<std::pair<char, int>> coords_tmp;
    
    for (int i = 0; i < 3; ++i) //3 = SHIP_CONST
    {
        std::cout << "Choose "<< i+1 << "field of your ship:\n ";
        std::getline(std::cin, input);
        //std::pair<char, int> tmp_pair = strToPair(input);
        coords_tmp.insert(strToPair(input));
                            

    }
    ships.emplace_back(coords_tmp);

    
}

} // namespace BattleShips