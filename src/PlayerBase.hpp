#pragma once
#include "Board.hpp"
#include "Coordinate.hpp"
#include "Logger.hpp"
#include "Ship.hpp"
#include <iostream>
#include <memory>

namespace BattleShips
{
class PlayerBase
{
public:
    inline void showBoard() const
    {
        board.printBoard();
    }

protected:
    uint8_t getSizeOfNewShip() const // could break in various ways maybe add some checks?
    {
        return general::shipSizes.at(shipsOwned.size());
    }

    mutable Board board{}; // opponentsBoard{};
    std::set<Ship> shipsOwned;
};

} // namespace BattleShips