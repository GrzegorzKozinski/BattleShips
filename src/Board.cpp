#include "Board.hpp"

#include <vector>
#include <iostream>

#include <memory>
#include <set>

namespace BattleShips{

Board::Board()
{
    
    for(int i = 0; i < BOARD_SIZE; ++i) letters.push_back(i + ASCII_INT_TO_LETTER);
    board_.push_back(letters);
    
    for(int i = 0; i < BOARD_SIZE; ++i) board_.push_back(std::vector<char>(BOARD_SIZE,' '));
    

    std::cout<< "Board constructed \n";
}

Board::~Board()
{
    std::cout<< "Board destroyed \n";
}

std::vector<std::vector<char>>& Board::getBoard()
{
    return board_;
}

void Board::boardView()
{
    for(uint32_t i = 0; i < board_.size(); ++i)
    {
        
        std::cout  << i << " | ";
       
        for (u_int32_t j = 0; j < board_.at(0).size(); ++j)
        {    
            std::cout << board_.at(i).at(j) << " | ";
        }
        
        std::cout<< "\n--|";

        for (u_int32_t j = 0; j < board_.at(0).size(); ++j) 
        {
            std::cout << "---|";
        }

        std::cout<< "\n";
    }
}



std::vector<Ship>& Board::getShips()
{
    return ships_;
}

void Board::shipsSetup()
{
    
    {   //manual ship setup
        ships_.emplace_back(std::set<std::pair<char, int>>{
        {'A', 1},
        {'A', 2},
        {'A', 3}});

        ships_.emplace_back(std::set<std::pair<char, int>>{
        {'C', 2},
        {'D', 2},
        {'E', 2},
        {'F', 2}});
    }
}
} // namespace BattleShips