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

        void printBoard() const;

        void clear();
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
        std::set<Coordinate> getNeighbourFields(const std::set<Coordinate> &shipCoords) const // 3rd and more fields setting
        {
            const auto firstShipFiled = shipCoords.cbegin();
            const auto lastShipFiled{--shipCoords.cend()};
            const bool sameLettersExpected{(*firstShipFiled).letter == (*lastShipFiled).letter}; // determine ship's orientation
            std::set<Coordinate> result(getAllSurroundingFields(shipCoords));
            if (sameLettersExpected) //erase different letters
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
            else if ((*firstShipFiled).digit == (*lastShipFiled).digit) //erase different digits
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
            else //should not happen
            {
                std::cout << "Error: Ship fields not in line" << std::endl;
            }
    
            return result;
        }
        
    private:
        
        GlobalSettings settings_;
        mutable Fields fields_{}; // board as  collection of Fields
    };
} // namespace BattleShips