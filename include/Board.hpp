#pragma once

#include <vector>
#include "Formatter.hpp"
#include "Ship.hpp"



namespace BattleShips{

//const int BOARD_SIZE(6);

//const int ASCII_INT_TO_LETTER(65);

class Board
{
private:

    std::vector<std::vector<char>> board_;
    std::vector<Ship> ships_;
    std::vector<char> letters;

public:

    Board();
    ~Board();

    void boardView();
    void shipsSetup();
    void viaCommunicatorSetup();
    std::vector<Ship>& getShips();
    
    void setShips(std::vector<Ship>& ships);
    std::vector<std::vector<char>>& getBoard();
};


} // namespace BattleShips