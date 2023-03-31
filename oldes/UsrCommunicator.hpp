#pragma once
#include <memory>

#include "Board.hpp"
#include "ICommunicator.hpp"

#include <iterator>
#include <algorithm>


namespace BattleShips{
    


class UsrCommunicator : public ICommunicator
{

private:

// Board& m_fields;
// std::vector<Ship>& ships;
std::unique_ptr<Formatter> formatter;

public:
    // UsrCommunicator(Board& board);
    UsrCommunicator() {};
    ~UsrCommunicator();

    // void shipPlacementGuide(std::vector<Ship>& ships) override;

    bool addField(const std::string& input, std::set<std::pair<char, int>>& coords_tmp);
    bool isTaken(std::vector<std::vector<char>>& board, const std::string& str) const;
    
   
};
} // namespace BattleShips