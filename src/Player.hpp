#pragma once

#include <iostream>
#include <memory>

#include "UsrCommunicator.hpp"
#include "Board.hpp"


namespace BattleShips{

//const int BOARD_SIZE(6);

//const int ASCII_INT_TO_LETTER(65);

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




