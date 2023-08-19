#pragma once
#include <cstdint>
#include <iostream>
#include <functional>
#include <set>

namespace BattleShips
{
struct Coordinate
{
    static constexpr int asciiIntToChar{65};
    char letter;
    uint8_t digit;

    Coordinate() : letter{'?'}, digit{std::numeric_limits<decltype(digit)>::max()} {} // default??
    Coordinate(const char c, const uint8_t d) : letter{c}, digit{d} {}

    std::pair<uint8_t, uint8_t> getIndices() const
    {
        return std::make_pair((this->letter - asciiIntToChar), this->digit - 1);
    }

    bool operator==(const Coordinate& other) const
    {
        return letter == other.letter and digit == other.digit;
    }

    bool operator<(const Coordinate& other) const
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

inline std::ostream& operator<<(std::ostream& os, const Coordinate& coord)
{
    os << coord.letter << (int)coord.digit; // cast to int cause uint8_t is treated like 'char'
    return os;
}
inline std::ostream& operator<<(std::ostream& os, const std::set<BattleShips::Coordinate>& set)
{
    os << "[ ";
    for (const auto& coord : set)
    {
        os << coord << " ";
    }
    os << "]";
    return os;
}

} // namespace BattleShips
