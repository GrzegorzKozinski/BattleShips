#pragma once

#include "Formatter.hpp"
#include "Ship.hpp"

#include <memory>
#include <vector>
#include <functional>
#include <iostream>
#include <set>
#include <algorithm>



const int ASCII_CHAR_TO_INT(48);
const int ASCII_INT_TO_LETTER(65);
const int BOARD_SIZE(8);
const int SHIP_SIZE(3); 

namespace BattleShips{
    
class Ship
{
private:
    static unsigned int shipIdCounter;
    std::set<std::pair<char, int>> coords_;
    unsigned shipSize;
    unsigned int shipId;
   
    
public:
    Ship(std::set<std::pair<char, int>> coords);
    ~Ship();

    unsigned int getShipId() const;
    void setShipId(unsigned int id);
    std::set<std::pair<char, int>> getCoords() const;
    void setCoord(std::pair<char, int>& coord);
    void printCoords();
    void markPosition(std::vector<std::vector<char>>& board);
    bool isFiledOnCoords(const std::pair<char, int>& p ) const;
    void surroundPosition(std::vector<std::vector<char>>& board);
};


} // namespace BattleShips
