#include "Ship.hpp"



namespace BattleShips{

unsigned int Ship::shipId = 0;

Ship::Ship(std::set<std::pair<char, int>> coords) : coords_(coords), shipSize(coords.size())
{
    
    shipId++;
    setShipId(shipId);
    printCoords();
    std::cout << "Ship #"<< getShipId()<<" constructed\n";
    
}

Ship::~Ship()
{
    std::cout << "Ship no."<<getShipId()<< " destroyed \n";
}

void Ship::setShipId(unsigned int& id)
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
    /*
    if(coords_.size() == 0) // 1st coordinate
    {
        coords_.push_back(coord);
        std::cout << "Ship: 1st coordinate set successfully\n";
        return 1;
    }

    if(coords_.size() == 1)
    {
        coords_.push_back(coord);
        std::cout << "Ship: 2nd coordinate set successfully\n";
        return 1;
    }
    */
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
    for(const auto& coord : getCoords()) //mark ships coords
    {     
        board.at(coord.second).at(coord.first-65) = 'X';
    }
}

bool Ship::isFiledOnCoords(const std::pair<char, int>& p ) const
{   
    //std::cout << "Ship::isFieldOnCoord - before find - shipId: " << getShipId() <<"\n";
    auto it = std::find(coords_.begin(), coords_.end(), p);
    //std::cout << "Ship::isFieldOnCoord - AFTER find \n";
    if(it != coords_.end()) //found
    {
        //std::cout << "Ship::isFieldOnCoord - found coord!\n";
        return true;
    }
    else    //not found
    {
        //std::cout << "Ship::isFieldOnCoord - coord NOT found\n";
        return false;
    }
        
    
    return false;
}
}// namespace BattleShips