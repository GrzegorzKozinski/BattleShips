#include <string>
#include "Logger.hpp"
#include "GlobalSettings.hpp"

namespace BattleShips{

template<class T>
void GlobalSettings::print(const T& container) const
{
    std::for_each(container.begin(), container.end(),
        [](const typename T::value_type& element){ std::cout << element << " ";});
    std::cout << std::endl;
}

GlobalSettings::GlobalSettings()
{
    for(uint64_t i = 0; i < general::boardSize; ++i) 
    {
        letters[i] =  general::asciiIntToChar + i; // board head will be letters ABC..., rows got numbers
    }
    std::cout <<"GlobalSettings c-tor\n";
}

// Static method to print dashed row
void GlobalSettings::print_dashed_row()
{
    std::cout<< "\n--|";
    for (uint32_t j = 0; j < general::boardSize; ++j) 
    {
        std::cout << "---|";
    }
    std::cout<< "\n";
}

// Static method to check if a value is outside the board range
bool GlobalSettings::isOutsideRange(const uint64_t i)
{
    return i > general::boardSize or i <= 0;
}

// Method to print header of the board
void GlobalSettings::printHeader() const
{
    std::cout  << "+ | ";
    for (uint32_t i = 0; i < general::boardSize; ++i)
    {
        std::cout  << letters[i] << " | ";
    }
    print_dashed_row();
}

// Method to check if a given character is contained in the array of letters
bool GlobalSettings::lettersContainChar(const char c) const
{
    return std::find(letters.begin(), letters.end(), c) != letters.end();
}

// Method to check if a given input string is invalid
bool GlobalSettings::isBadInput(const std::string& input) const
{
    std::cout << "Input is "<< input << "\n";
    if(input.size() == 2)
    {
        const auto charFromCoordinate = static_cast<char>(input[0]);
        if(not lettersContainChar(charFromCoordinate)) // 
        {
            std::cout << "1st coordinate " << charFromCoordinate << " invalid\n";
            return true;
        }
        else
        {
            const auto secondCoordinate = static_cast<uint64_t>(input[1] - general::asciiCharToInt);
            if (isOutsideRange(secondCoordinate))
            {
                std::cout <<"2nd coordinate " << secondCoordinate << " outside range: 0 " << general::boardSize << "\n";
                return true;
            }
        }
        return false;
    }
    std::cout <<"Bad input length (" << input.size() << ")\n"; 
    return true;
}

// Method to get a field from user input
Coordinate GlobalSettings::getFieldFromUser() const
{
    std::string userInput;
    Coordinate c;
    do
    {
        std::cout << "Type coordinate: \n";
        userInput.clear();
        std::cin >> userInput;
    }
    while(isBadInput(userInput));
    c.letter = userInput[0];
    c.digit = std::stoi(userInput.substr(1));
    log("GlobalSettings: coordinate is ", c.letter, c.digit);
    return c;
}

// Method to get the index of a character in the array of letters
uint8_t GlobalSettings::indexOf(const char c) const
{
    std::cout << "indexOf: char to find: "  << c << "\n";
    const auto itr = std::find(letters.begin(), letters.end(), c);
    return std::distance(letters.begin(), itr); // simpler and letter should already be checked during user input validation
}
// bool GlobalSettings::isFieldInLine(const Coordinate& newCoord, const std::set<Coordinate>& set) const
// {
//     if(set.size() == 0 ) return true;
//     return isAlingnedHorizantally(newCoord, set) or isAlignedVertically(newCoord, set);
// }

// bool GlobalSettings::isAlingnedHorizantally(const Coordinate& newCoord, const std::set<Coordinate>& set) const
// {
//     return std::all_of(set.begin(), set.end(), [&](const Coordinate& coord){return coord.letter == newCoord.letter;});
// }
// bool GlobalSettings::isAlignedVertically(const Coordinate& newCoord, const std::set<Coordinate>& set) const
// {
//     return std::all_of(set.begin(), set.end(), [&](const Coordinate& coord){return coord.digit == newCoord.digit;});
// }
char GlobalSettings::lastLetter() const
{
    return letters.back();
} 
}//namespace BattleShips