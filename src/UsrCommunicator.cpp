#include "UsrCommunicator.hpp"

namespace BattleShips{

UsrCommunicator::UsrCommunicator()
{
    for(int i = 0; i < BOARD_SIZE; ++i)  letters.push_back(i + ASCII_INT_TO_LETTER);
    std::cout << "UsrCommunicator created!\n";
}

UsrCommunicator::~UsrCommunicator()
{
    std::cout << "UsrCommunicator destroyed!\n";
}

std::pair<char, int> UsrCommunicator::strToPair(const std::string& str)
{
    std::pair<char, int> p(str.at(0), str.at(1)-ASCII_CHAR_TO_INT);
  
    return p;
}

bool UsrCommunicator::isTaken(std::vector<Ship>& ships, const std::pair<char, int>& input) const
{
    for(auto& ship : ships)
    {
        if(ship.isFiledOnCoords(input)) return true; 
    }
    return false;
}

void UsrCommunicator::shipPlacementGuide(std::vector<Ship>& ships)
{   
    std::string input;
   
    std::set<std::pair<char, int>> coords_tmp;
    int i = 0;
   
    do
    {
        std::cout << "Choose 1. field of your ship:\n ";
        std::getline(std::cin, input);
        
    }while(properInputFormat(input, coords_tmp, ships) == false ); //first field input chceck
    coords_tmp.insert(strToPair(input));
    do
    {
        std::cout << "Choose 2. field of your ship:\n ";
        std::getline(std::cin, input);
        
    }while(properInputFormat(input, coords_tmp, ships) == false ); //second field input chceck
    coords_tmp.insert(strToPair(input));
    do
    {
        std::cout << "Choose 3. field of your ship:\n ";
        std::getline(std::cin, input);
        
    }while(properInputFormat(input, coords_tmp, ships) == false ); //third field input chceck
    coords_tmp.insert(strToPair(input));
   

    
    ships.emplace_back(coords_tmp);

}

bool UsrCommunicator::properInputFormat(const std::string& input)
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

bool UsrCommunicator::properInputFormat(const std::string& input, std::set<std::pair<char, int>>& coords_tmp, std::vector<Ship>& ships)
{
    bool fieldTaken = true;
    auto inputPair = strToPair(input);
    if(properInputFormat(input) == false)
    {
        std::cout<< "Invalid input";
        return false;
    }
    switch (coords_tmp.size())
    {
    case (0):
    {
    fieldTaken = isTaken(ships, inputPair);
    
    if(fieldTaken == false)            
    {
       
        std::cout << "Field " << input << " OK\n";
        return true;
    }
    else
    {
        std::cout << "Invalid Field\n";
        return false;
    }
    }

    case (1):
    {
    fieldTaken = isTaken(ships, inputPair);
    auto it = std::find(coords_tmp.begin(), coords_tmp.end(), inputPair);
    auto first_coord = *coords_tmp.begin();
    if(fieldTaken == false && it == coords_tmp.end() && fieldNeigbour(coords_tmp, inputPair) == true)            
    {
        std::cout << "Field " << input << " OK\n";
        return true;
    }
    else
    {
        std::cout << "Invalid Field\n";
        return false;
    }
    }
    case (2):
    {
    fieldTaken = isTaken(ships, inputPair);
    auto it = std::find(coords_tmp.begin(), coords_tmp.end(), inputPair);
    auto first_coord = *coords_tmp.begin();
   
    if(fieldTaken == false && it == coords_tmp.end() && fieldNeigbour(coords_tmp, inputPair) == true)            
    {
        std::cout << "Field " << input << " OK\n";
        return true;
    }
    else
    {
        std::cout << "Invalid Field\n";
        return false;
    }
    }
    default:
    {
    std::cout << "Invalid input\n";
    return false;
    }
    }

    return false;
   
}

bool UsrCommunicator::fieldNeigbour(const std::set<std::pair<char, int>>& fields, std::pair<char, int>& inputPair)
{
    std::set<std::pair<char, int>> fieldNeigbours;
    
    for(const auto& field : fields)
    {
        fieldNeigbours.insert({field.first-1, field.second});
        fieldNeigbours.insert({field.first+1, field.second});
        fieldNeigbours.insert({field.first, field.second-1});
        fieldNeigbours.insert({field.first, field.second+1});
    }
    /*
     std::set<int> c = {1, 2, 3, 4, 5, 6, 7, 8, 9};
 
    // erase all odd numbers from c
    for(auto it = c.begin(); it != c.end(); ) {
        if(*it % 2 == 1)
            it = c.erase(it);
        else
            ++it;
    }
 
    for(int n : c) {
        std::cout << n << ' ';
    }
    */
    if(fields.size() > 1) 
    {
        auto firstField =  *(fields.begin());
        auto secondField = *(std::next(fields.begin(),1));
        if(firstField.first == secondField.first)
        {
            std::cout<<"Same column - remove fields from diff cols";
            for(auto it = fieldNeigbours.begin(); it != fieldNeigbours.end(); )
            {
            
                if((*it).first != firstField.first ) it = fieldNeigbours.erase(it);
                else ++it;
       
            }
        }
       
        
        if(firstField.second == secondField.second)
        {
            std::cout<<"Same row - remove fields from diff rows";
            for(auto it = fieldNeigbours.begin(); it != fieldNeigbours.end(); )
            {

                if((*it).second != firstField.second) it = fieldNeigbours.erase(it);
                else ++it;
       
            }
        }
       
    }
    
    
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