#pragma once

#include "Ship.hpp"

namespace BattleShips{
    
class Communicator
{
private:
   
public:
    Communicator();
    ~Communicator();

    std::pair<char, int> strToPair(const std::string& str);
    bool isTaken(std::vector<Ship>& ships, const std::pair<char, int>& input) const;
    void shipPlacementGuide(std::vector<Ship>& ships);
   
};
} // namespace BattleShips