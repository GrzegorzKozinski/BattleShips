#include "Communicator.hpp"

namespace BattleShips{

Communicator::Communicator()
{
    for(int i = 0; i < BOARD_SIZE; ++i)  letters.push_back(i + ASCII_INT_TO_LETTER);
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
    
    for(auto& ship : ships)
    {
        if(ship.isFiledOnCoords(input)) return true; 
    }
    return false;
}

void Communicator::shipPlacementGuide(std::vector<Ship>& ships)
{   
    std::string input;
   
    std::set<std::pair<char, int>> coords_tmp;
    int i = 0;
    bool fieldTaken=true;
    
   
    do
    {
        std::cout << "Choose field of your ship:\n ";
        std::getline(std::cin, input);
       
        if(properInputFormat(input) == true)
        {
            fieldTaken = isTaken(ships, strToPair(input));
            auto it = std::find(coords_tmp.begin(), coords_tmp.end(), strToPair(input));
            if(fieldTaken == false && it == coords_tmp.end())
            {
                coords_tmp.insert(strToPair(input));
                std::cout << "Field " << input << " added\n";
                ++i;
            }
            else
            {
                std::cout << "Field "<< input <<" already taken\n";
            }
            
        }
        else
        {
            std::cout << "Invalid input\n";
        }
        
    std::cout << " i = " << i;
    }while(i < 3);
    ships.emplace_back(coords_tmp);

}

bool Communicator::properInputFormat(const std::string& input)
{
    if(input.size() != 2) return false; 

    auto it = std::find(letters.begin(), letters.end(), input.at(0));
    
    if(it == letters.end()) return false;
    if((input.at(1) - 48) < 1 || (input.at(1) - 48)  > BOARD_SIZE )
    {
        return false;
    }
   
   
    

    return true;
    
    
}

}// namespace BattleShips