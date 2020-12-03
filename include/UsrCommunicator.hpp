#pragma once
#include <memory>

#include "Board.hpp"
#include "ICommunicator.hpp"
#include "Formatter.hpp"
#include <iterator>
#include <algorithm>


namespace BattleShips{
    


class UsrCommunicator : public ICommunicator
{

private:

Board& board_;
std::vector<Ship>& ships;
std::unique_ptr<Formatter> formatter;

public:
    UsrCommunicator(Board& board);
    ~UsrCommunicator();

    void shipPlacementGuide(std::vector<Ship>& ships) override;

    //std::pair<char, int> strToPair(const std::string& str);
   
    bool addField(const std::string& input, std::set<std::pair<char, int>>& coords_tmp);
   
    
   
};
} // namespace BattleShips