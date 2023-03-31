#pragma once

#include "Ship.hpp"

#include <utility>
#include <iostream>
#include <set>
#include <algorithm>

namespace BattleShips{

class Formatter
{
private:


public:
    Formatter();
    ~Formatter() = default;

    std::pair<char, int> strToPair(const std::string& str);

    bool properInputFormat(const std::pair<char, int>& inputPair);
    bool properInputFormat(const std::string& input);
    bool properInputFormat(const std::string& input, std::set<std::pair<char, int>>& coords_tmp);

    bool fieldNeighbour(std::set<std::pair<char, int>>& coords_tmp, std::pair<char, int>& input);
    
};
} // namespace BattleShips