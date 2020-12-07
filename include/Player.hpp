#pragma once

#include <iostream>
#include <memory>

#include "ICommunicator.hpp"

#include "UsrCommunicator.hpp"

namespace BattleShips{


class Player
{
private:
    std::unique_ptr<Board> boardPtr;
    std::unique_ptr<ICommunicator> commPtr;
public:
    Player();
    ~Player();
};
} // namespace BattleShips




