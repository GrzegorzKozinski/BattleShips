#pragma once
#include <array>
#include <iostream>
#include <functional>
#include <algorithm>
#include <set>
#include "Coordinate.hpp"
#include <cassert>

namespace BattleShips
{
    class GlobalSettings
    {
    public:
        GlobalSettings();
        static void print_dashed_row();
        static bool isOutsideRange(const uint64_t i);
        void printHeader() const;
        bool lettersContainChar(const char c) const;
        bool isBadInput(const std::string &input) const;
        Coordinate getFieldFromUser(const std::string& prompt = "Type coordinate: \n") const;
        uint8_t indexOf(const char c) const;
        template <class T>
        inline void print(const T& container) const;
        char lastLetter() const; 

    private:
        std::array<char, general::boardSize> letters{};
    };
}
