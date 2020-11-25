#include "Player.hpp"

namespace BattleShips{
    
Player::Player() 
{
    Board board;
    commPtr = std::make_unique<UsrCommunicator>(&board);
    board.boardView();
    std::cout << "Player created\n";
}

Player::~Player()
{
    std::cout << "Player destroyed\n";
}
} //namespace BattleShips
