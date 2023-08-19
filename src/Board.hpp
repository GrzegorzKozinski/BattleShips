#pragma once
#include "EField.hpp"
#include "Coordinate.hpp"
#include "general.hpp"
#include "Logger.hpp"
#include <set>
#include <array>

namespace BattleShips
{

using Fields = std::array<std::array<EField, general::boardSize>, general::boardSize>;

class Board
{
public:
    Board();
    ~Board();
    void clear();
    void printBoard() const;
    Fields getFields() const;
    EField getField(const Coordinate& coordinate) const;
    void setField(const Coordinate& coordinate, const EField field)
    {
        const auto idx{coordinate.getIndices()};
        log("Board::setField: expectedShipCoordinate", idx.first, idx.second);

        fields_[idx.first][idx.second] = field;
    }
    EField& getFieldRef(const Coordinate& coordinate) const;
    void markNewShipPosition(const std::set<Coordinate>& shipCoords);
    void surroundShipsWithMissFields(const std::set<Coordinate>& shipCoords);
    bool isFieldFree(const Coordinate& coordinate) const;
    std::set<Coordinate> getAllSurroundingFields(const std::set<Coordinate>& shipCoords) const;
    std::set<Coordinate> getNeighbourFields(const Coordinate& baseCoordinate) const; // second field setup
    std::set<Coordinate> getNeighbourFields(const std::set<Coordinate>& shipCoords) const;
    bool notProperForCreatingShip(const Coordinate& coord) const;

private:
    void removeOtherThanEmptyFields(std::set<Coordinate>& coords) const;

    mutable Fields fields_{}; // board as  collection of Fields
};
} // namespace BattleShips