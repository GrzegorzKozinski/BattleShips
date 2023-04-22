#pragma once
#include "Logger.hpp"
#include <iostream>
#include <memory>
#include <set>
#include "Logger.hpp"
#include "Board.hpp"
#include "Ship.hpp"
#include "GlobalSettings.hpp"
#include "Coordinate.hpp"

namespace BattleShips
{
    class Player
    {

    public:
        GlobalSettings settings_;
        Player();
        ~Player();

        inline void showBoard() const
        {
            board.printBoard();
        }

        void shipsSetup()
        {
            for (auto i{0}; i < general::numOfShipsPerPlayer; ++i)
            {
                std::set<Coordinate> shipCoords{getNewShipCoords()};
                board.markNewShipPosition(shipCoords);
                board.surroundShipsWithMissFields(shipCoords);
                shipsOwned.emplace(shipCoords); // when set of Coords are valid finally create ship based on them

                showBoard();
            }
        }

        std::set<Coordinate> getNewShipCoords() const
        {
            std::set<Coordinate> ship{getFreeCoordinateFromUser()}; // init with first coordinate
            const uint8_t shipSize{getSizeOfNewShip()};

            for (auto i{1}; i < shipSize; ++i) // loop through rest fields
            {
                const std::set<Coordinate> pool = (ship.size() == 1) ? board.getNeighbourFields(*ship.begin()) : board.getNeighbourFields(ship);

                std::cout << "Valid options are: "<< pool << "\n";
                Coordinate nextCoord;
                do
                {
                    nextCoord = settings_.getFieldFromUser();
                } while (pool.find(nextCoord) == pool.end()); // until pool finds nextCoord

                ship.insert(nextCoord);
            }
            return ship;
        }

    private:
        uint8_t getSizeOfNewShip() const // could break in various ways maybe add some checks?
        {
            return general::shipSizes.at(shipsOwned.size());
        }

        Coordinate getFreeCoordinateFromUser() const
        {
            Coordinate coord; // user input validated
            do
            {
                coord = settings_.getFieldFromUser();
            } while (not board.isFieldFree(coord));
            return coord;
        }

        mutable Board board{}; // opponentsBoard{};
        std::set<Ship> shipsOwned;
    };
} // namespace BattleShips
