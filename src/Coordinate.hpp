#pragma once
#include <functional>
#include "general.hpp"

class GlobalSettings;
namespace BattleShips
{
    struct Coordinate
    {
        // static constexpr int asciiIntToChar{65};
        char letter;
        int digit;

        Coordinate() : letter{'y'}, digit{666} {} // default??
        Coordinate(const char c, const int d) : letter{c}, digit{d} {}

        std::pair<uint8_t, uint8_t> getIndices() const
        {
            return std::make_pair((this->letter - general::asciiIntToChar), this->digit - 1);
        }

        bool operator==(const Coordinate &other) const
        {
            return letter == other.letter and digit == other.digit;
        }

        bool operator<(const Coordinate &other) const
        {
            if (letter < other.letter)
            {
                return true;
            }
            else if (letter == other.letter)
            {
                return digit < other.digit;
            }
            else
                return false;
            // strict weak ordering needs to be satisfied
        }
    };

    inline std::ostream &operator<<(std::ostream &os, const Coordinate &coord)
    {
        os << coord.letter << coord.digit;
        return os;
    }
    inline std::ostream &operator<<(std::ostream &os, const std::set<BattleShips::Coordinate> &set)
    {
        os << "[ ";
        for (const auto &coord : set)
        {
            os << coord << " ";
        }
        os << "]";
        return os;
    }

} // namespace BattleShips
