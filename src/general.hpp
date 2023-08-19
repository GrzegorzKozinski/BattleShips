#pragma once
#include <algorithm>
#include <array>
#include <iostream>
#include "Coordinate.hpp"
#include "Logger.hpp"


namespace general
{
using BattleShips::Coordinate;
static constexpr uint8_t boardSize{6};
class Settings
{
public:
    Settings() : letters{fillLetters()} {}
    std::array<char, boardSize> getLetters() const {return letters;}
private:
    const std::array<char, boardSize> letters{};
    std::array<char, boardSize> fillLetters()
    {
        std::array<char, boardSize> arr{};
        for (uint64_t i = 0; i < boardSize; ++i)
        {
            arr[i] = 'A' + i; // board head will be letters ABC..., rows got numbers
        }
        return arr;
    }
};
static const Settings settings{};
static constexpr uint8_t numOfShipsPerPlayer{2};
static constexpr std::array<uint8_t, numOfShipsPerPlayer> shipSizes{3, 3}; // ship size and count
static constexpr int asciiCharToInt{48};
// static constexpr GlobalSettings{};

static void print_dashed_row()
{
    std::cout << "\n--|";
    for (uint32_t j = 0; j < boardSize; ++j)
    {
        std::cout << "---|";
    }
    std::cout << "\n";
}
static void printHeader()
{
    std::cout << "+ | ";
    for (uint32_t i = 0; i < boardSize; ++i)
    {
        std::cout << settings.getLetters()[i] << " | ";
    }
    print_dashed_row();
}
static inline char lastLetter() { return settings.getLetters().back(); }
static bool isOutsideRange(const uint8_t i)
{
    return i > boardSize or i <= 0;
}
static bool lettersContainChar(const char c)
{
    return std::find(settings.getLetters().begin(), settings.getLetters().end(), c) != settings.getLetters().end();
}
static bool isBadInput(const std::string& input)
{
    log("Input is", input);
    if (input.size() == 2)
    {
        const auto charFromCoordinate = static_cast<char>(input[0]);
        if (not lettersContainChar(charFromCoordinate)) //
        {
            std::cout << "1st coordinate " << charFromCoordinate << " invalid\n";
            return true;
        }
        else
        {
            const auto secondCoordinate = static_cast<uint8_t>(input[1] - asciiCharToInt);
            if (isOutsideRange(secondCoordinate))
            {
                std::cout << "2nd coordinate " << secondCoordinate << " outside range: 0 " << boardSize << "\n";
                return true;
            }
        }
        return false;
    }
    std::cout << "Bad input length (" << input.size() << ")\n";
    return true;
}

static Coordinate getFieldFromUser(const std::string& prompt = "Type coordinate: \n")
{
    std::string userInput;
    Coordinate c;
    do
    {
        std::cout << prompt;
        userInput.clear();
        std::cin >> userInput;
    } while (isBadInput(userInput));
    c.letter = userInput[0];
    c.digit = std::stoul(userInput.substr(1));
    log("GlobalSettings: coordinate is ", c.letter, c.digit);
    return c;
}
} // namespace general