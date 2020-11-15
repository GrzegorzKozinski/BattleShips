#pragma once

#include "Ship.hpp"

namespace BattleShips{
    
const int ASCII_INT_TO_LETTER(65);
const int BOARD_SIZE(6);
class Communicator
{

private:
std::vector<char> letters;
public:
    Communicator();
    ~Communicator();

    std::pair<char, int> strToPair(const std::string& str);
    bool isTaken(std::vector<Ship>& ships, const std::pair<char, int>& input) const;
    void shipPlacementGuide(std::vector<Ship>& ships);
    bool properInputFormat(const std::string& input);
   
};
} // namespace BattleShips