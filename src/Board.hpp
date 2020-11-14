#pragma once

#include <vector>

#include "Ship.hpp"
#include "Communicator.hpp"


namespace BattleShips{

const int BOARD_SIZE(6);
const int SHIP_CONST(3);
const int ASCII_CHAR_TO_INT(65);

class Board
{
private:

    std::vector<std::vector<char>> board;
    std::vector<Ship> ships;
    std::vector<char> letters;

public:

    Board();
    ~Board();

    void boardView();
    void shipsSetup();
    void viaCommunicatorSetup();
    std::vector<std::vector<char>> getBoard();
};


} // namespace BattleShips