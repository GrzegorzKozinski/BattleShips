#pragma once

#include <iostream>
#include <memory>

#include "Board.hpp"


namespace BattleShips{

class Player
{
private:
    std::unique_ptr<Board> boardPtr;

public:
    Player();
    ~Player();
};
} // namespace BattleShips




