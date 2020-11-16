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
    std::pair<char, int> p(str.at(0), str.at(1)-ASCII_CHAR_TO_INT);
  
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
   
    
    //full path for setting up one ship
    do
    {
        std::cout << "Choose 1. field of your ship:\n ";
        std::getline(std::cin, input);
        if(properInputFormat(input)) addField(input,coords_tmp,ships);
    }while(properInputFormat(input) == false ); //first field input chceck
    //addField(input,coords_tmp,ships);
    do
    {
        std::cout << "Choose 2. field of your ship:\n ";
        std::getline(std::cin, input);

        if(properInputFormat(input)) addField(input,coords_tmp,ships);
    }while(properInputFormat(input) == false); //second field
    //addField(input,coords_tmp,ships);

    // addField(input, coords_tmp, ships);
        //addField(input)
        //std::cout << "Choose 2. field of your ship:\n ";
        //std::getline(std::cin, input);
        // addField(input, coords_tmp);

        //std::cout << "Choose 3. field of your ship:\n ";
        //std::getline(std::cin, input);
        //addField(input, coords_tmp);

    //std::cout << " i = " << i;
    //}while(i < 3);
    ships.emplace_back(coords_tmp);

}

bool Communicator::properInputFormat(const std::string& input)
{
    if(input.size() != 2) return false; 

    auto it = std::find(letters.begin(), letters.end(), input.at(0));
    if(it == letters.end()) return false;

    if((input.at(1) - ASCII_CHAR_TO_INT) < 1 || (input.at(1) - ASCII_CHAR_TO_INT)  > BOARD_SIZE )
    {
        return false;
    }

    return true;
}

bool Communicator::addField(const std::string& input, std::set<std::pair<char, int>>& coords_tmp, std::vector<Ship>& ships)
{
    bool fieldTaken = true;
    auto inputPair = strToPair(input);

    switch (coords_tmp.size())
    {
    case (0):
    fieldTaken = isTaken(ships, inputPair);
    //auto it = std::find(coords_tmp.begin(), coords_tmp.end(), inputPair);
    if(fieldTaken == false)            
    {
        coords_tmp.insert(inputPair);
        std::cout << "Field " << input << " added\n";
        return true;
    }
    else
    {
        std::cout << "Field " << input <<" already taken\n";
        return false;
    }
    
    
    
    std::cout << "Invalid input\n";
    return false;
    


    case (1):
   
    fieldTaken = isTaken(ships, inputPair);
    auto it = std::find(coords_tmp.begin(), coords_tmp.end(), inputPair);
    auto first_coord = *coords_tmp.begin();
    if(fieldTaken == false && it == coords_tmp.end() && fieldNeigbour(first_coord, inputPair) == true)            
    {
        coords_tmp.insert(inputPair);
        std::cout << "Field " << input << " added\n";
        return true;
    }
    else
    {
        std::cout << "Field " << input <<" already taken\n";
        return false;
    }
    
    std::cout << "Invalid input\n";
    return false;

   
        
    }
    return false;
}

bool Communicator::fieldNeigbour(const std::pair<char, int>& field, std::pair<char, int>& inputPair)
{
    std::set<std::pair<char, int>> fieldNeigbours{ //initialization?
        {field.first-1, field.second},
        {field.first+1, field.second},
        {field.first, field.second-1},
        {field.first, field.second+1}
    };
    auto it = std::find(fieldNeigbours.begin(), fieldNeigbours.end(), inputPair);
    if(it != fieldNeigbours.end())
    {
        return true;
    }
    else
    {
        return false;
    }
}

}// namespace BattleShips