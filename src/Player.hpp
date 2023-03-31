#pragma once

#include <iostream>
#include <memory>
#include <set>

#include "Board.hpp"
#include "Ship.hpp"
#include "GlobalSettings.hpp"


namespace BattleShips{


class Player
{
private:

    mutable Board board{};  // opponentsBoard{};
    std::set<Ship> shipsOwned;

public:
    GlobalSettings settings_;
    Player(); 
    ~Player();
    void showBoard() const
    {
        board.printBoard();
    }
    Board& getBoard()
    {
        return board;
    }
    
    uint8_t getSizeOfNewShip() const // could break in various ways maybe add some checks?
    {
        return general::shipSizes.at(shipsOwned.size());
    }

    std::set<Coordinate> getNewShipCoords() const
    {
        const uint8_t shipSize{ getSizeOfNewShip() };
        std::set<Coordinate> shipCoords;

        for(auto i{0}; i < shipSize; ++i)
        {
            Coordinate coordinate{}; //user input validated
            do
            {
                coordinate = settings_.getFieldFromUser();
            }
            while (not isFieldFree(coordinate));       // 1 is this field free
            // generateNextPossibleFields();
            settings_.isFieldInLine(coordinate, shipCoords); // 2 is it in one line

            // isFieldTouchingOtherShip(coordinate);   // 3 is this  touching other ship?
            shipCoords.insert(coordinate); // find batter place for this method? Like Utils?
        }
        return shipCoords;
    }
    bool isFieldFree(const Coordinate& coordinate) const
    {
        printf("isFieldFree: coordinate is %c %d \n", static_cast<char>(coordinate.letter), coordinate.digit);
        const bool empty{board.getField(coordinate) == EField::EMPTY};
        if(not empty) std::cout << "This field is not empty!\n"; 
        return empty;
    }

    void shipsSetup()
    {
        for(auto i{0}; i < general::numOfShipsPerPlayer; ++i)
        {
            std::set<Coordinate> shipCoords;

            // user input vaildated through settings Class
            // shipCoords = getNewShipCoords();
            // do
            // {
            //    shipCoords = getNewShipCoords();
            // }
            // while(isValidShipCoords(shipCoords));

            shipCoords = getNewShipCoords();
            board.markNewShipPosition(shipCoords);
            shipsOwned.emplace(shipCoords); // when set of Coords are valid finally create ship based on them
        }
    }

    std::set<Coordinate> getNextPossibleFields(const Coordinate& baseCoordinate) const
    {
        std::set<Coordinate> result;
        const auto l = baseCoordinate.letter;
        const auto d = baseCoordinate.digit;

        if (l != 'A') result.emplace(l - 1, d);
        if (l != settings_.lastLetter()) result.emplace(l + 1, d);
        if (d != 1) result.emplace(l, d - 1);
        if (d != general::boardSize) result.emplace(l, d + 1);
        return result;
    }
    //place all ships
            //place 1st to last - repeat numOfShipsPerPlayer times +
                // determine size of ship - n +
                // n times get field from user + 
                // verify ok/nok
                    // verify user input (format) +
                    // isInLine or setOrientation -
                    // isTouchingOtherShip? - 
                // getNewShipCoords(setOfCoords coords)
};
} // namespace BattleShips




