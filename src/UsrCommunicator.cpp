#include "UsrCommunicator.hpp"

namespace BattleShips{

UsrCommunicator::UsrCommunicator(Board& board) : board_(board), ships(board_.getShips())
{
    formatter = std::make_unique<Formatter>();
   
    shipPlacementGuide(ships);
    ships.back().markPosition(board_.getBoard());
    ships.back().surroundPosition(board_.getBoard());
   
    board_.boardView();

    shipPlacementGuide(ships);
    ships.back().markPosition(board_.getBoard());
    ships.back().surroundPosition(board_.getBoard());

    std::cout << "UsrCommunicator created!\n";
}

UsrCommunicator::~UsrCommunicator()
{
    std::cout << "UsrCommunicator destroyed!\n";
}


void UsrCommunicator::shipPlacementGuide(std::vector<Ship>& ships)
{   
    std::string input;
   
    std::set<std::pair<char, int>> coords_tmp;
    
    while(coords_tmp.size() < SHIP_SIZE)
    {
        do
        {
            std::cout << "Choose "<< coords_tmp.size() + 1 <<". field of your ship:\n ";
            std::getline(std::cin, input);
            

        }while(formatter->properInputFormat(input, coords_tmp) == false || isTaken(board_.getBoard(), input) == true ); // field input chceck

        coords_tmp.insert(formatter -> strToPair(input));
    }
    ships.emplace_back(coords_tmp);
    
    

}

bool UsrCommunicator::isTaken(std::vector<std::vector<char>>& board, const std::string& str) const
{
    int row,col;
    row = str.at(0) - ASCII_INT_TO_LETTER;
    col = str.at(1) - ASCII_CHAR_TO_INT;
    
    if(board.at(col).at(row) != ' ')
    {
        std::cout<<"Field is not empty!\n";
        return true;
    }
    return false;
} 



}// namespace BattleShips