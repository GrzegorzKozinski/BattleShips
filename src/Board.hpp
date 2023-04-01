#pragma once

#include "EField.hpp"
#include "GlobalSettings.hpp"
#include <set>

namespace BattleShips{

using Fields = std::array<std::array<EField, general::boardSize>, general::boardSize>;

class Board
{
public:
    Board();
    ~Board();

    void printBoard() const;
    void shipsSetup();
    void clear();
    Fields getFields() const; 
    EField getField(const Coordinate& coordinate) const;
    void setField(const Coordinate& coordinate, const EField fieldType )
    {
        const auto idx {coordinate.getIndices()};
           std::cout << "expectedShipCoordinate" << idx.first
        << idx.second << "\n";

        fields_[idx.first][idx.second] = fieldType;
    }
    EField& getFieldRef(const Coordinate& coordinate) const;
    void markNewShipPosition(const std::set<Coordinate>& shipCoords)
    {
        for(const auto& coordinate : shipCoords)
        {
            setField(coordinate, EField::SHIP);
        }
    }

private:
    GlobalSettings settings_;
    mutable Fields fields_{}; // board as  collection of Fields
};
} // namespace BattleShips