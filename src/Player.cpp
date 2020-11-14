#include "Player.hpp"

namespace BattleShips{
    
Player::Player() 
{
    boardPtr = std::make_unique<Board>();
    std::cout << "Player created\n";
}

Player::~Player()
{
    std::cout << "Player destroyed\n";
}
} //namespace BattleShips
