#pragma once
#include "PlayerBase.hpp"

namespace BattleShips
{
class Player : private PlayerBase
{
public:
    void shipsSetup();
    std::set<Coordinate> getNewShipCoords() const;

private:
    Coordinate getFirstCoordFromUser() const;
};
} // namespace BattleShips
