#include "Player.hpp"
#include <memory>

// toDo
// place usings in one place
// place statics in one place


int main()
{ 
    // two paradigms of object creation order
    // top -> down or down -> top like should we create whole game then smallest fields? Or other way round?
    // 1) e
    // game host and rounds in higher scope
    // 
    BattleShips::Player p1; //Test with only one player
    p1.showBoard();
    p1.shipsSetup();
    // std::unique_ptr<BattleShips::Board> board_p = std::make_unique<BattleShips::Board>();
    // board_p->printBoard();
    // BattleShips::Board b{};
    // Host -> Player -> Boards -> Ships + Tiles 

    return 0;
}
