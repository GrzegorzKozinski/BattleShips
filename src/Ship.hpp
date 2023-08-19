#pragma once

#include "Coordinate.hpp"
#include "Logger.hpp"
#include <algorithm>
#include <iostream>


static constexpr int SHIP_SIZE(3);

namespace BattleShips
{

class Ship
{
private:
    static uint64_t shipIdCounter;
    std::set<Coordinate> coords_;

    uint64_t shipId;
public:
    explicit Ship(const std::set<Coordinate>& coords);
    ~Ship();

    uint64_t getShipId() const;
    void setShipId(uint64_t id);
    void setCoord(Coordinate& coord);
    void printCoords() const;
    bool isFiledOnCoords(const Coordinate& p) const;
    bool operator<(const Ship& other) const;
};

} // namespace BattleShips
