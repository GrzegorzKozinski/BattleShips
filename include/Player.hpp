#pragma once

#include <iostream>
#include <memory>

#include "UsrCommunicator.hpp"
#include "Board.hpp"


namespace BattleShips{


class Player
{
private:
    std::unique_ptr<Board> boardPtr;
    std::unique_ptr<UsrCommunicator> commPtr;
public:
    Player();
    ~Player();
};
} // namespace BattleShips




