#pragma once

#include <functional>
#include <iostream>
#include <set>


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
    void setShipId(unsigned int& id);
    std::set<std::pair<char, int>> getCoords() const;
    void setCoord(std::pair<char, int>& coord);
    void printCoords();
    void markPosition(std::vector<std::vector<char>>& board);
    bool isFiledOnCoords(const std::pair<char, int>& p ) const;
};


} // namespace BattleShips
