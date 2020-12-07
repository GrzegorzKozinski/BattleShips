#include "Formatter.hpp"

namespace BattleShips{

Formatter::Formatter()
{
    for(int i = 0; i < BOARD_SIZE; ++i)  letters.push_back(i + ASCII_INT_TO_LETTER);
}

std::pair<char, int> Formatter::strToPair(const std::string& str)
{
    std::pair<char, int> p(str.at(0), str.at(1)-ASCII_CHAR_TO_INT);
    return p;
}

bool Formatter::properInputFormat(const std::pair<char, int>& inputPair)
{
  

    auto it = std::find(letters.begin(), letters.end(), inputPair.first); //repeated code in overloaded method
    if(it == letters.end()) return false;

    if((inputPair.second < 1) || (inputPair.second > BOARD_SIZE )) //repeated code in overloaded method
    {
        return false;
    }

    return true;
}
bool Formatter::properInputFormat(const std::string& input)
{
    if(input.size() != 2) return false; 

    auto it = std::find(letters.begin(), letters.end(), input.at(0)); //repeated code in overloaded method
    if(it == letters.end()) return false;

    if((input.at(1) - ASCII_CHAR_TO_INT) < 1 || (input.at(1) - ASCII_CHAR_TO_INT)  > BOARD_SIZE ) //repeated code in overloaded method
    {
        return false;
    }

    return true;
}
bool Formatter::properInputFormat(const std::string& input, std::set<std::pair<char, int>>& coords_tmp)
{
    
    if(properInputFormat(input) == false) return false;
   
    auto inputPair = strToPair(input);
   
    switch (coords_tmp.size())
    {
    case (0):
    {
        //std::cout << "Field " << input << " OK\n";
        return true;
    }

    case (1):
    {
    
    auto it = std::find(coords_tmp.begin(), coords_tmp.end(), inputPair);
   
    if(fieldNeighbour(coords_tmp, inputPair) == true && it == coords_tmp.end() )            
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
    
    auto it = std::find(coords_tmp.begin(), coords_tmp.end(), inputPair);
   
    if(fieldNeighbour(coords_tmp, inputPair) == true && it == coords_tmp.end() )            
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
bool Formatter::fieldNeighbour(std::set<std::pair<char, int>>& coords_tmp, std::pair<char, int>& inputPair)
{
    std::set<std::pair<char, int>> tmp_set, fieldNeighbours;
    
    for(const auto& field : coords_tmp)
    {
        
        if(properInputFormat(std::pair<char,int>(field.first-1, field.second)))
          fieldNeighbours.insert({field.first-1, field.second});

        if(properInputFormat(std::pair<char,int>(field.first+1, field.second))) 
            fieldNeighbours.insert({field.first+1, field.second});

        if(properInputFormat(std::pair<char,int>(field.first, field.second-1))) 
            fieldNeighbours.insert({field.first, field.second-1});
            
        if(properInputFormat(std::pair<char,int>(field.first, field.second+1))) 
            fieldNeighbours.insert({field.first, field.second+1});
    }
    
    if(coords_tmp.size() > 1) //erase not allowed fields  
    {
        auto firstField =  *(coords_tmp.begin());
        auto secondField = *(std::next(coords_tmp.begin(),1));
        fieldNeighbours.erase(firstField);
        fieldNeighbours.erase(secondField);
        if(firstField.first == secondField.first)
        {
            for(auto it = fieldNeighbours.begin(); it != fieldNeighbours.end(); )
            {
                if((*it).first != firstField.first ) it = fieldNeighbours.erase(it);
                else ++it;
            }
        }
       
        
        if(firstField.second == secondField.second)
        {
            for(auto it = fieldNeighbours.begin(); it != fieldNeighbours.end(); )
            {
                if((*it).second != firstField.second) it = fieldNeighbours.erase(it);
                else ++it;
            }
        }
       
    }
    
    if(fieldNeighbours.size() == 0)
    {
        std::cout<<"No more possible fields to place - erasing last placed fields!\n";
        coords_tmp.clear();
    }
    auto it = std::find(fieldNeighbours.begin(), fieldNeighbours.end(), inputPair);
    if(it != fieldNeighbours.end())
    {
        return true;
    }
    else
    {
        return false;
    }
    return false;
}

   
    
}// namespace BattleShips