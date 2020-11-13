
#pragma once

#include <utility>
#include <set>
#include <vector>
#include <iostream>
#include <vector>
#include <memory>

namespace BattleShips
{
class Ship
{
private:
static unsigned int shipId;
std::set<std::pair<char, int>> coords_;
unsigned shipSize; 
    
public:
    Ship(std::set<std::pair<char, int>> coords);
    ~Ship();
    
    bool operator <(const Ship& other) const;
    unsigned int getShipId() const;
    std::set<std::pair<char, int>> getCoords() const;
    void setCoord(std::pair<char, int>& coord);
    void printCoords();
    void markPosition(std::vector<std::vector<char>>& board);
};


} // namespace BattleShips
