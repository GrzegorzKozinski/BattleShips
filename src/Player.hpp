#include "Board.cpp"

namespace BattleShips
{

class Player
{
private:
std::unique_ptr<Board> boardPtr;



public:
    Player();
    ~Player();
    
};

Player::Player() 
{
    boardPtr = std::make_unique<Board>();
    
    std::cout << "Player created\n";
    //cos w stylu:
    //communicator niech odpowiada za komunikacje z userem,
    //niech sprawdza poprawność?? i niech wykonuje i informuje usera
    
    
}

Player::~Player()
{
    std::cout << "Player destroyed\n";
}
} // namespace BattleShips




