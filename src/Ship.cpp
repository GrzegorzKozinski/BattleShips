
#include "Formatter.hpp"

namespace BattleShips{

unsigned int Ship::shipIdCounter = 0;

Ship::Ship(std::set<std::pair<char, int>> coords) : coords_(coords), shipSize(coords.size())
{
    setShipId(shipIdCounter);
    shipIdCounter++;
    //formatter = std::make_unique<Formatter>();
    
    std::cout << "Ship #"<< getShipId()<<" constructed\n";
}

Ship::~Ship()
{
    std::cout << "Ship #"<<getShipId()<< " destroyed \n";
}

void Ship::setShipId(unsigned int id)
{
    shipId = id;
}

unsigned int Ship::getShipId() const
{
    return shipId;
}

std::set<std::pair<char, int>> Ship::getCoords() const
{
    return coords_;
}

void Ship::setCoord(std::pair<char, int>& coord)
{
    coords_.insert(coord);
}

void Ship::printCoords()
{
    std::cout << "Ship coordinates: [ ";
    for(const auto& coord : coords_)
    {
        std::cout << coord.first << coord.second << " ";
    }
    std::cout << " ]\n";
}

void Ship::markPosition(std::vector<std::vector<char>>& board)
{
    for(const auto& coord : getCoords()) 
    {     
        board.at(coord.second).at(coord.first-65) = 'X';
    }
}

bool Ship::isFiledOnCoords(const std::pair<char, int>& p ) const
{   
    auto it = std::find(coords_.begin(), coords_.end(), p);
    if(it != coords_.end()) 
    {
        return true;
    }
    else    
    {
        return false;
    }
}
void Ship::surroundPosition(std::vector<std::vector<char>>& board)
{
    std::unique_ptr<Formatter> formatter =std::make_unique<Formatter>();
    std::set<std::pair<char, int>> tmpSet, shipNeighbours;
    for(const auto& field : coords_)
    {
         if(formatter->properInputFormat(std::pair<char,int>(field.first-1, field.second)))
          tmpSet.insert({field.first-1, field.second});

        if(formatter->properInputFormat(std::pair<char,int>(field.first+1, field.second))) 
            tmpSet.insert({field.first+1, field.second});

        if(formatter->properInputFormat(std::pair<char,int>(field.first, field.second-1))) 
            tmpSet.insert({field.first, field.second-1});
            
        if(formatter->properInputFormat(std::pair<char,int>(field.first, field.second+1))) 
            tmpSet.insert({field.first, field.second+1});
    }
    
    std::set_difference(tmpSet.begin(), tmpSet.end(),coords_.begin(), coords_.end(),
        std::inserter(shipNeighbours,shipNeighbours.end())); //exclude own body from marking


    for(auto& field : shipNeighbours) // mark surrounding on board
    {
        board.at(field.second).at(field.first-65) = 'o';
    }

}

}// namespace BattleShips