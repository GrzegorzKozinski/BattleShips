#pragma once
#include "Logger.hpp"
#include "EField.hpp"
#include "GlobalSettings.hpp"
#include <set>

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
        EField getField(const Coordinate &coordinate) const;
        void setField(const Coordinate &coordinate, const EField field)
        {
            const auto idx{coordinate.getIndices()};
            log("Board::setField: expectedShipCoordinate", idx.first, idx.second );
            // std::cout << "expectedShipCoordinate" << idx.first << idx.second << "\n";//

            fields_[idx.first][idx.second] = field;
        }
        EField &getFieldRef(const Coordinate &coordinate) const;
        void markNewShipPosition(const std::set<Coordinate> &shipCoords);
        void surroundShipsWithMissFields(const std::set<Coordinate> &shipCoords);
        bool isFieldFree(const Coordinate &coordinate) const;
        std::set<Coordinate> getAllSurroundingFields(const std::set<Coordinate> &shipCoords) const;
        std::set<Coordinate> getNeighbourFields(const Coordinate &baseCoordinate) const; // second field setup
        std::set<Coordinate> getNeighbourFields(const std::set<Coordinate> &shipCoords)const ;
        bool notProperForCreatingShip(const Coordinate& coord) const;
 
    private:
        void removeOtherThanEmptyFields(std::set<Coordinate> &coords) const;
        GlobalSettings settings_;
        mutable Fields fields_{}; // board as  collection of Fields
    };
} // namespace BattleShips