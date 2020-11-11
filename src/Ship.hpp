
#include <utility>
#include <set>
#include <vector>
#include <iostream>
#include <vector>
#include <memory>




namespace BattleShips
{
    class Ship
{
private:
std::set<std::pair<char, int>> coords_;
unsigned shipSize; 
    
public:
    Ship(std::set<std::pair<char, int>> coords);
    ~Ship();

    std::set<std::pair<char, int>> getCoords();
    void setCoord(std::pair<char, int>& coord);
    void printCoords();
    void markPosition(std::vector<std::vector<char>>& board);
};

Ship::Ship(std::set<std::pair<char, int>> coords) :  coords_(coords), shipSize(coords.size())
{
    std::cout << "Ship constructed \n";
}

Ship::~Ship()
{
    std::cout << "Ship destroyed \n";
}

std::set<std::pair<char, int>> Ship::getCoords()
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
    for(auto& coord : getCoords()) //mark ships coords
    {     
        board.at(coord.second).at(coord.first-65) = 'X';
    }
}

} // namespace BattleShips
