#pragma once

#include <iostream>
#include <memory>
#include <set>

#include "Board.hpp"
#include "Ship.hpp"
#include "GlobalSettings.hpp"

namespace BattleShips
{

    class Player
    {
    private:
        mutable Board board{}; // opponentsBoard{};
        std::set<Ship> shipsOwned;

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
            } while (not isFieldFree(firstCoord)); // 1 is this field free
            shipCoords.insert(firstCoord);         // find batter place for this method? Like Utils?
            // can be extracted: get rest fields;
            const uint8_t shipSize{getSizeOfNewShip()};
            for (auto i{1}; i < shipSize; ++i) // loop through rest fields
            {
                const std::set<Coordinate> pool = getNextPossibleFields(firstCoord);
                Coordinate nextCoord;
                nextCoord = settings_.getFieldFromUser();
                std::cout << "poolfind != pool.end()? " << (pool.find(nextCoord) != pool.end()) << std::endl;
                // do
                // {

                // } while (pool.find(nextCoord) != pool.end()); // until pool finds nextCoord

                settings_.isFieldInLine(firstCoord, shipCoords); // 2 is it in one line
                // settings_.getFieldFromUser(); //just 3rd
                // isFieldTouchingOtherShip(firstCoord);   // 3 is this  touching other ship?
                shipCoords.insert(nextCoord);
            }
            return shipCoords;
        }
        bool isFieldFree(const Coordinate &coordinate) const
        {
            printf("isFieldFree: coordinate is %c %d \n", static_cast<char>(coordinate.letter), coordinate.digit);
            const bool empty{board.getField(coordinate) == EField::EMPTY};
            if (not empty)
                std::cout << "This field is not empty!\n";
            return empty;
        }
        void shipsSetup()
        {
            for (auto i{0}; i < general::numOfShipsPerPlayer; ++i)
            {
                std::set<Coordinate> shipCoords;

                shipCoords = getNewShipCoords();
                board.markNewShipPosition(shipCoords);
                shipsOwned.emplace(shipCoords); // when set of Coords are valid finally create ship based on them
            }
        }

        std::set<Coordinate> getNextPossibleFields(const std::set<Coordinate> &shipCoords) const
        {
            std::set<Coordinate> result;

            const auto first = shipCoords.cbegin();
            const auto last{--shipCoords.cend()};
            const bool sameLettersExpected{(*first).letter == (*last).letter}; // determine ship's orientation
           
            auto possibleFields = getNextPossibleFields(*first);
            result.insert(possibleFields.begin(), possibleFields.end());
            possibleFields = getNextPossibleFields(*last);
            result.insert(possibleFields.begin(), possibleFields.end());

            for (auto it{shipCoords.begin()}; it != shipCoords.end(); ++it)
            {
                const auto matchingField = std::find(result.cbegin(), result.cend(), *it);
                if (matchingField != result.end()) // ship field found among result fields
                {
                    result.erase(*matchingField);
                }
            }

            if (sameLettersExpected) // erase fields with different letter from pool
            {
                for (auto it{result.begin()}; it != result.end();)
                {
                    if ((*it).letter != (*first).letter)
                        it = result.erase(it);
                    else
                        ++it;
                }
            }
            else if ((*first).digit == (*last).digit) // erase fields with different digit from pool
            {
                for (auto it{result.begin()}; it != result.end();)
                {

                    if ((*it).digit != (*first).digit)
                        it = result.erase(it); //
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

        std::set<Coordinate> getNextPossibleFields(const Coordinate &baseCoordinate) const
        {
            std::set<Coordinate> result;
            const auto l = baseCoordinate.letter;
            const auto d = baseCoordinate.digit;

            if (l != 'A')
                result.emplace(l - 1, d);
            if (l != settings_.lastLetter())
                result.emplace(l + 1, d);
            if (d != 1)
                result.emplace(l, d - 1);
            if (d != general::boardSize)
                result.emplace(l, d + 1);
            return result;
        }
        // place all ships
        // place 1st to last - repeat numOfShipsPerPlayer times +
        //  determine size of ship - n +
        //  n times get field from user +
        //  verify ok/nok
        //  verify user input (format) +
        //  isInLine or setOrientation -
        //  isTouchingOtherShip? -
        // getNewShipCoords(setOfCoords coords)
    };
} // namespace BattleShips
