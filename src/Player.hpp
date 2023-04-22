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

        void showBoard() const
        {
            board.printBoard();
        }
        Board &getBoard()
        {
            return board;
        }

        uint8_t getSizeOfNewShip() const // could break in various ways maybe add some checks?
        {
            return general::shipSizes.at(shipsOwned.size());
        }

        std::set<Coordinate> getNewShipCoords() const
        {
            // could be extracted: get1stFiled ...

            std::set<Coordinate> shipCoords;
            Coordinate firstCoord{}; // user input validated
            do
            {
                firstCoord = settings_.getFieldFromUser();
            } while (not isFieldFree(firstCoord)); // 1 is this field free broken
            shipCoords.insert(firstCoord);         // find batter place for this method? Like Utils?
            // can be extracted: get rest fields;
            setNextFields(shipCoords);
            return shipCoords;
        }

        bool isFieldFree(const Coordinate &coordinate) const
        {
            const bool empty{board.getField(coordinate) == EField::EMPTY};
            if (not empty)
                std::cout << "This field is not empty!\n";
            return empty;
        }

        void shipsSetup()
        {
            for (auto i{0}; i < general::numOfShipsPerPlayer; ++i)
            {
                std::set<Coordinate> shipCoords{getNewShipCoords()};
                board.markNewShipPosition(shipCoords);
                shipsOwned.emplace(shipCoords); // when set of Coords are valid finally create ship based on them
            }
        }

        std::set<Coordinate> getNextPossibleFields(const std::set<Coordinate> &shipCoords) const // 3rd and more fields setting
        {
            const auto firstShipFiled = shipCoords.cbegin();
            const auto lastShipFiled{--shipCoords.cend()};

            std::set<Coordinate> result{getNextPossibleFields(*firstShipFiled)};
            log("Result after init: ", result.size());
            const auto possibleFields{getNextPossibleFields(*lastShipFiled)};
            result.insert(possibleFields.begin(), possibleFields.end());
            log("Result after possibleFields: ", result.size());
            for (auto it{shipCoords.begin()}; it != shipCoords.end(); ++it)
            {
                const auto matchingField = std::find(result.begin(), result.end(), *it);
                if (matchingField != result.end()) // ship field found among result fields
                {
                    result.erase(*matchingField);
                }
            }
            const bool sameLettersExpected{(*firstShipFiled).letter == (*lastShipFiled).letter}; // determine ship's orientation
            log("SameLettersExpected: ", sameLettersExpected);
            if (sameLettersExpected) // erase fields with different letter from pool
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
            else if ((*firstShipFiled).digit == (*lastShipFiled).digit) // erase fields with different digit from pool
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
            else
            {
                std::cout << "Error: Ship fields not in line" << std::endl;
            }
            // getNextPossibleFields for 1st then add for 2nd then excude all coords from ^shipCoords
            return result;
        }

        std::set<Coordinate> getNextPossibleFields(const Coordinate &baseCoordinate) const // second field setup
        {
            log("Player::getNextPossibleFields(const Coordinate &baseCoordinate)");
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

    private:
        void setNextFields(std::set<Coordinate> &ship) const
        {
            // log("Set next field");
            const uint8_t shipSize{getSizeOfNewShip()};

            assert(ship.size() == 1);
            for (auto i{1}; i < shipSize; ++i) // loop through rest fields
            {
                const std::set<Coordinate> pool = (ship.size() == 1) ? 
                getNextPossibleFields(*ship.begin()) : 
                getNextPossibleFields(ship);

                log("Player::setNextFields: poolIs  ", pool);
                Coordinate nextCoord;
                do
                {
                    nextCoord = settings_.getFieldFromUser();
                    auto coordNotFound{pool.find(nextCoord) == pool.end()};
                     log("Player::setNextFields: coord not found?: ", coordNotFound);
                } while (pool.find(nextCoord) == pool.end()); // until pool finds nextCoord

                // isFieldTouchingOtherShip(firstCoord);   // 3 is this  touching other ship?

                ship.insert(nextCoord);
            }
        }

        mutable Board board{}; // opponentsBoard{};
        std::set<Ship> shipsOwned;
    };
} // namespace BattleShips

// place all ships
// place 1st to lastShipFiled - repeat numOfShipsPerPlayer times +
//  determine size of ship - n +
//  n times get field from user +
//  verify ok/nok
//  verify user input (format) +
//  isInLine or setOrientation -
//  isTouchingOtherShip? -
// getNewShipCoords(setOfCoords coords)