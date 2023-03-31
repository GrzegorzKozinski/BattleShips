#include "UsrCommunicator.hpp"

namespace BattleShips{

// UsrCommunicator::UsrCommunicator(Board& board) : m_fields(board), ships(m_fields.getShips())
// {
//     formatter = std::make_unique<Formatter>();
   
//     shipPlacementGuide(ships);
//     ships.back().markPosition(m_fields.getFields());
//     ships.back().surroundPosition(m_fields.getFields());
   
//     m_fields.printBoard();

//     shipPlacementGuide(ships);
//     ships.back().markPosition(m_fields.getFields());
//     ships.back().surroundPosition(m_fields.getFields());

//     std::cout << "UsrCommunicator created!\n";
// }

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
            
        }while(formatter->properInputFormat(input, coords_tmp) == false ); // field input chceck
        // }while(formatter->properInputFormat(input, coords_tmp) == false || isTaken(m_fields.getFields(), input) == true ); // field input chceck

        coords_tmp.insert(formatter -> strToPair(input));
    }
    ships.emplace_back(coords_tmp);
    
    

}

bool UsrCommunicator::isTaken(std::vector<std::vector<char>>& board, const std::string& str) const
{
    int row,col;
    row = str.at(0) - asciiIntToChar;
    col = str.at(1) - asciiCharToInt;
    
    if(board.at(col).at(row) != ' ')
    {
        std::cout<<"Field is not empty!\n";
        return true;
    }
    return false;
} 



}// namespace BattleShips