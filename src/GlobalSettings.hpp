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

        // constexpr int getBoardSize();
        bool lettersContainChar(const char c) const;
        bool isBadInput(const std::string &input) const;

        Coordinate getFieldFromUser() const;

        uint8_t indexOf(const char c) const;
        bool isFieldInLine(const Coordinate &newCoord, const std::set<Coordinate> &set) const;

        template <class T>
        inline void print(const T& container) const;
        char lastLetter() const; 

    private:
        bool isAlingnedHorizantally(const Coordinate &newCoord, const std::set<Coordinate> &set) const;
        bool isAlignedVertically(const Coordinate &newCoord, const std::set<Coordinate> &set) const;
        std::array<char, general::boardSize> letters{};
    };
} // namespace BattleShips
  // globals
  //  bool operator<(const Coordinate &lhs, const Coordinate &rhs)
  //  {
  //      if (lhs.letter < rhs.letter)
  //      {
  //          return true;
  //      }
  //      else if (lhs.letter == rhs.letter)
  //      {
  //          return lhs.digit < rhs.digit;
  //      }
  //      else
  //      {
  //          return false;
  //      }
  //  }

// bool operator==(const Coordinate &lhs, const Coordinate &rhs) const
// {
//     return lhs.letter == rhs.letter && lhs.digit == rhs.digit;
// }