
// #include "Formatter.hpp"
#include "Ship.hpp"
namespace BattleShips
{

uint64_t Ship::shipIdCounter{0};

Ship::Ship(const std::set<Coordinate>& coords) : coords_{coords}
{
    setShipId(shipIdCounter);
    ++shipIdCounter;

    log("Ship #",getShipId()," constructed\n");
}

Ship::~Ship()
{
    log("Ship #",getShipId()," destroyed\n");
}

void Ship::setShipId(uint64_t id)
{
    shipId = id;
}

uint64_t Ship::getShipId() const
{
    return shipId;
}

void Ship::setCoord(Coordinate& coord)
{
    coords_.insert(coord);
}

void Ship::printCoords() const
{
    std::cout << "Ship coordinates: [ ";
    for (const auto& coord : coords_)
    {
        std::cout << coord.letter << coord.digit << " ";
    }
    std::cout << " ]\n";
}

bool Ship::isFiledOnCoords(const Coordinate& p) const
{
    return std::find(coords_.begin(), coords_.end(), p) != coords_.end();
}
bool Ship::operator<(const Ship& other) const
{
    return this->getShipId() < other.getShipId();
}

// void Ship::surroundPosition(std::vector<std::vector<char>>& board) //
// {
//     std::unique_ptr<Formatter> formatter =std::make_unique<Formatter>();
//     std::set<Coordinate> tmpSet, shipNeighbours;
//     for(const auto& field : coords_)
//     {
//          if(formatter->properInputFormat(std::pair<char,int>(field.first-1, field.second)))
//           tmpSet.insert({field.first-1, field.second});

//         if(formatter->properInputFormat(std::pair<char,int>(field.first + 1, field.second)))
//             tmpSet.insert({field.first+1, field.second});

//         if(formatter->properInputFormat(std::pair<char,int>(field.first, field.second-1)))
//             tmpSet.insert({field.first, field.second-1});

//         if(formatter->properInputFormat(std::pair<char,int>(field.first, field.second+1)))
//             tmpSet.insert({field.first, field.second+1});
//     }

//     std::set_difference(tmpSet.begin(), tmpSet.end(),coords_.begin(), coords_.end(),
//         std::inserter(shipNeighbours,shipNeighbours.end())); //exclude own body from marking

//     for(auto& field : shipNeighbours) // mark surrounding on board
//     {
//         board.at(field.second).at(field.first-65) = 'o';
//     }

// }

} // namespace BattleShips