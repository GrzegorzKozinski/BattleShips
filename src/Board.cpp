#include "Board.hpp"

#include <vector>
#include <iostream>

#include <memory>
#include <set>

namespace BattleShips{

Board::Board()
{
    
    for(int i = 0; i < BOARD_SIZE; ++i) letters.push_back(i + ASCII_INT_TO_LETTER);
    board.push_back(letters);
    
    //std::vector<std::vector<char>> borad(BOARD_SIZE, std::vector<char>(BOARD_SIZE, ' '));

    for(int i = 0; i < BOARD_SIZE; ++i) board.push_back(std::vector<char>(BOARD_SIZE,' '));
    
    //shipsSetup();

    viaCommunicatorSetup();
    
    for(auto& ship : ships) // marks all its ships on board
    {
        ship.markPosition(board); 
    }
    boardView();

    std::cout<< "Board constructed \n";
}

Board::~Board()
{
    std::cout<< "Board destroyed \n";
}

void Board::viaCommunicatorSetup()
{
    std::unique_ptr<UsrCommunicator> commPtr = std::make_unique<UsrCommunicator>();

    commPtr -> shipPlacementGuide(ships);
    
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
    
    {   //manual ship setup
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
}
} // namespace BattleShips