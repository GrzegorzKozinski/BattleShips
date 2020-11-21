#pragma once

#include "ICommunicator.hpp"
#include<iterator>

namespace BattleShips{
    
const int ASCII_CHAR_TO_INT(48);
const int ASCII_INT_TO_LETTER(65);
const int BOARD_SIZE(6);

class UsrCommunicator : public ICommunicator
{

private:
std::vector<char> letters;
public:
    UsrCommunicator();
    ~UsrCommunicator();

    void shipPlacementGuide(std::vector<Ship>& ships) override;

    std::pair<char, int> strToPair(const std::string& str);
    bool isTaken(std::vector<Ship>& ships, const std::pair<char, int>& input) const;
    bool properInputFormat(const std::string& input);
    bool addField(const std::string& input, std::set<std::pair<char, int>>& coords_tmp, std::vector<Ship>& ships);
    bool properInputFormat(const std::string& input, std::set<std::pair<char, int>>& coords_tmp, std::vector<Ship>& ships);
    bool fieldNeigbour(const std::set<std::pair<char, int>>& fields, std::pair<char, int>& input);
   
};
} // namespace BattleShips