#include "Player.hpp"

namespace BattleShips
{
void Player::shipsSetup()
{
    showBoard();
    for (auto i{0}; i < general::numOfShipsPerPlayer; ++i)
    {
        std::set<Coordinate> shipCoords{getNewShipCoords()};
        board.markNewShipPosition(shipCoords);
        board.surroundShipsWithMissFields(shipCoords);
        shipsOwned.emplace(shipCoords); // when set of Coords are valid finally create ship based on them
        showBoard();
    }
}
std::set<Coordinate> Player::getNewShipCoords() const
{
    std::set<Coordinate> ship{}; // init with first coordinate
    const uint8_t shipSize{getSizeOfNewShip()};

    for (auto i{1}; i < shipSize; ++i) // loop through rest fields
    {
        if (ship.empty()) //first coord
        {
            ship.insert(getFirstCoordFromUser()); // take  outside for loop?
        }
        const std::set<Coordinate> pool = (ship.size() == 1) ? board.getNeighbourFields(*ship.begin()) : board.getNeighbourFields(ship);
        if (pool.empty())
        {
            showBoard();
            log("Ship setup not possible there, choose another location.", *ship.begin(), "is not good place to start with...");
            i = 0;
            ship.clear();
            continue;
        }
        std::cout << "Valid options are: " << pool << "\n";
        Coordinate nextCoord;
        do
        {
            nextCoord = general::getFieldFromUser();
        } while (pool.find(nextCoord) == pool.end()); // until valid option chosen

        ship.insert(nextCoord);
    }
    return ship;
}
Coordinate Player::getFirstCoordFromUser() const
{
    Coordinate coord; // user input validated
    do
    {
        coord = general::getFieldFromUser("Place new ship starting field:\n");
    } while (board.notProperForCreatingShip(coord));
    return coord;
}
} // namespace BattleShips
