#include "Board.hpp"

#include <vector>
#include <iostream>
#include <memory>
#include <set>

namespace BattleShips
{

    Board::Board()
    {
        clear();
        std::cout << "Board constructed \n";
    }

    Board::~Board()
    {
        std::cout << "Board destroyed \n";
    }

    Fields Board::getFields() const
    {
        return fields_;
    }

    void Board::clear()
    {
        for (uint64_t col{0}; col < fields_.size(); ++col)
        {
            fields_[col].fill(EField::EMPTY); // fill board with empty fields
        }
    }

    EField Board::getField(const Coordinate &coordinate) const
    {
        const auto idx{coordinate.getIndices()};
        printf("getField: letterIdx is %d digitIdx is %d \n", idx.first, idx.second);
        return fields_[idx.first][idx.second]; // to test thiws method
    }

    EField &Board::getFieldRef(const Coordinate &coordinate) const
    {
        const auto idx{coordinate.getIndices()};
        return fields_[idx.first][idx.second];
    }

    void Board::printBoard() const // pretty print board
    {
        settings_.printHeader();
        for (uint64_t i = 0; i < fields_.size(); ++i)
        {
            std::cout << i + 1 << " | ";
            for (uint64_t j = 0; j < fields_.at(0).size(); ++j)
            {
                std::cout << fields_.at(j).at(i) << " | ";
            }
            GlobalSettings::print_dashed_row();
        }
    }

    void Board::markNewShipPosition(const std::set<Coordinate> &shipCoords)
    {
        for (const auto &coordinate : shipCoords)
        {
            setField(coordinate, EField::SHIP);
        }
    }

    void Board::surroundShipsWithMissFields(const std::set<Coordinate> &shipCoords)
    {
        const auto fieldsToSetAsMiss{getAllSurroundingFields(shipCoords)};
        for (const auto &coord : fieldsToSetAsMiss)
        {
            setField(coord, EField::MISSED);
        }
    }

    std::set<Coordinate> Board::getAllSurroundingFields(const std::set<Coordinate> &shipCoords) const
    {
        std::set<Coordinate> result{};
        for (const auto &coord : shipCoords)
        {
            result.merge(getNeighbourFields(coord));
        }

        for (auto it{shipCoords.begin()}; it != shipCoords.end(); ++it)
        {
            const auto matchingField = std::find(result.begin(), result.end(), *it);
            if (matchingField != result.end()) // ship field found among result fields
            {
                result.erase(*matchingField);
            }
        }
        log("all neighbours:", result);
        return result;
    }
    
    bool Board::isFieldFree(const Coordinate &coordinate) const
    {
        const bool empty{getField(coordinate) == EField::EMPTY};
        if (not empty)
        {
            log("This field is not empty!");
        }
        return empty;
    }

    bool Board::notProperForCreatingShip(const Coordinate& coord) const
    {
        const bool isBadField{not isFieldFree(coord) or getNeighbourFields(coord).empty()};
        if(isBadField) 
        {
            log("Cant place new ship here!");
        }
        return isBadField;
    }

    std::set<Coordinate> Board::getNeighbourFields(const Coordinate &baseCoordinate) const // second field setup
    {
        log("Player::getNeighbourFields(const Coordinate &baseCoordinate)");
        std::set<Coordinate> result;
        const auto l = baseCoordinate.letter;
        const auto d = baseCoordinate.digit;

        if (l != 'A')
            result.emplace(l - 1, d);
        if (l != settings_.lastLetter())
            result.emplace(l + 1, d);
        if (d != 1)
            result.emplace(l, d - 1);
        if (d != general::boardSize) // last digit
            result.emplace(l, d + 1);
        removeOtherThanEmptyFields(result);
        return result;
    }

    std::set<Coordinate> Board::getNeighbourFields(const std::set<Coordinate> &shipCoords) const// 3rd and more fields setting
    {
        const auto firstShipFiled = shipCoords.cbegin();
        const auto lastShipFiled{--shipCoords.cend()};
         // determine ship's orientation
        std::set<Coordinate> result{getAllSurroundingFields(shipCoords)};
     
        const bool sameLettersExpected{(*firstShipFiled).letter == (*lastShipFiled).letter};
        if (sameLettersExpected) // erase different letters
        {
            log("same letters branch");
            for (auto it{result.begin()}; it != result.end();)
            {
                if ((*it).letter != (*firstShipFiled).letter)
                    it = result.erase(it);
                else
                    ++it;
            }
        }
        else if ((*firstShipFiled).digit == (*lastShipFiled).digit) // erase different digits
        {
            log("same digit branch");
            for (auto it{result.begin()}; it != result.end();)
            {

                if ((*it).digit != (*firstShipFiled).digit)
                    it = result.erase(it);
                else
                    ++it;
            }
        }
        else // should not happen
        {
            std::cout << "Error: Ship fields not in line" << std::endl;
        }
        return result;
    }

    void Board::removeOtherThanEmptyFields(std::set<Coordinate> &coords) const
    {
    for (auto it{coords.begin()}; it != coords.end();)
        {
            if (not isFieldFree(*it))
                it = coords.erase(it);
            else
                ++it;
        }
    }
} // namespace BattleShips