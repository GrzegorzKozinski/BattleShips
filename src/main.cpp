#include "Player.hpp"
#include <memory>

int main()
{ 
    BattleShips::Player p1; //Test with only one player
    p1.showBoard();
    p1.shipsSetup();
    return 0;
}
