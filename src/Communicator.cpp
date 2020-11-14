#include "Communicator.hpp"

namespace BattleShips{

Communicator::Communicator()
{
    std::cout << "Communicator created!\n";
}

Communicator::~Communicator()
{
    std::cout << "Communicator destroyed!\n";
}

std::pair<char, int> Communicator::strToPair(const std::string& str)
{
    std::pair<char, int> p(str.at(0), str.at(1)-48);
  
    return p;
}

bool Communicator::isTaken(std::vector<Ship>& ships, const std::pair<char, int>& input) const
{
    int n = 0;
    //std::cout << "isTaken - size of ships: " << ships.size() << '\n';
    for(auto& ship : ships)
    {
        //std::cout << "isTaken - for loop: " << n++ << " run \n";
        if(ship.isFiledOnCoords(input)) return true; 
    }
    return false;
}

void Communicator::shipPlacementGuide(std::vector<Ship>& ships)
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
    }while(i < 3);
    ships.emplace_back(coords_tmp);

}

}// namespace BattleShips