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
            std::cout << "This field is not empty!\n";
        }
        return empty;
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
        return result;
    }
} // namespace BattleShips