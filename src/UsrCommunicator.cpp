#include "UsrCommunicator.hpp"

namespace BattleShips{

UsrCommunicator::UsrCommunicator(Board& board) : board_(board), ships(board_.getShips())
{
    formatter = std::make_unique<Formatter>();
   

    shipPlacementGuide(ships);
    shipPlacementGuide(ships);
    
    for(auto& ship : ships) // marks all its ships on board
    {
        ship.markPosition(board_.getBoard()); 
        ship.surroundPosition(board_.getBoard());
    } 
    std::cout << "UsrCommunicator created!\n";
}

UsrCommunicator::~UsrCommunicator()
{
    std::cout << "UsrCommunicator destroyed!\n";
}

/* std::pair<char, int> UsrCommunicator::strToPair(const std::string& str)
{
    std::pair<char, int> p(str.at(0), str.at(1)-ASCII_CHAR_TO_INT);
    return p;
} */

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

        }while(formatter->properInputFormat(input, coords_tmp) == false ); // field input chceck

        coords_tmp.insert(formatter -> strToPair(input));
    }
    ships.emplace_back(coords_tmp);
    
    

}





}// namespace BattleShips