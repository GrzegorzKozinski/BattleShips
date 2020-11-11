#include "Ship.hpp"

using namespace BattleShips;
namespace BattleShips
{

const int BOARD_SIZE(6);
const int SHIP_CONST(3);

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

Board::Board()
{
    
    for(int i = 0; i < BOARD_SIZE; ++i) letters.push_back(i+65);
    board.push_back(letters);

    for(int i = 0; i < BOARD_SIZE; ++i)
    {
        std::vector<char> tmp;
        for (int j = 0; j < BOARD_SIZE; ++j)
        {
            tmp.push_back(' ');  
        }
        board.push_back(tmp);
        
    }
    

    shipsSetup();
    //viaCommunicatorSetup();

    boardView();

    std::cout<< "Board constructed \n";
}

Board::~Board()
{
    std::cout<< "Board destroyed \n";
}
void Board::viaCommunicatorSetup()
{
    //std::unique_ptr<Communicator> commPtr = std::make_unique<Communicator>();

   // commPtr -> shipPlacementGuide(ships);
}
void Board::boardView()
{
   
   
    for(uint32_t i = 0; i < board.size(); ++i)
    {
        
        std::cout  << i << " | ";
       
        for (u_int32_t j = 0; j < board.at(0).size(); ++j)
        {    
            std::cout << board.at(i).at(j) << " | ";
        }
        
        std::cout<< "\n--|";

        for (u_int32_t j = 0; j < board.at(0).size(); ++j) 
        {
            std::cout << "---|";
        }

        std::cout<< "\n";
      
    }
}
void Board::shipsSetup()
{
    
    
    
    { // manual ship setup
        ships.emplace_back(std::set<std::pair<char, int>>{
        {'A', 1},
        {'A', 2},
        {'A', 3}});

        ships.emplace_back(std::set<std::pair<char, int>>{
        {'C', 2},
        {'D', 2},
        {'E', 2},
        {'F', 2}});
    }
    
    for(auto& ship : ships) 
    {
        ship.printCoords(); //print ship coords 
        ship.markPosition(board); 

    }
}
} // namespace BattleShips