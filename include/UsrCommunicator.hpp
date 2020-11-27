#pragma once
#include <memory>

#include "Board.hpp"
#include "ICommunicator.hpp"
#include<iterator>
#include<algorithm>

namespace BattleShips{
    


class UsrCommunicator : public ICommunicator
{

private:
std::vector<char> letters;
Board& board_;
std::vector<Ship>& ships;
public:
    UsrCommunicator(Board& board);
    ~UsrCommunicator();

    void shipPlacementGuide(std::vector<Ship>& ships) override;

    std::pair<char, int> strToPair(const std::string& str);
    bool isTaken(std::vector<Ship>& ships, const std::pair<char, int>& input) const;
    bool addField(const std::string& input, std::set<std::pair<char, int>>& coords_tmp);
    bool properInputFormat(const std::pair<char, int>& inputPair);
    bool properInputFormat(const std::string& input);
    bool properInputFormat(const std::string& input, std::set<std::pair<char, int>>& coords_tmp);
    bool fieldNeighbour(std::set<std::pair<char, int>>& coords_tmp, std::pair<char, int>& input);
   
};
} // namespace BattleShips