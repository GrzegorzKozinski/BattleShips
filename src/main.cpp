#include <algorithm>
#include <set>
#include <functional>
#include <iostream>

#include "Player.hpp"
#include "Communicator.hpp"
#include "Ship.hpp"

using namespace BattleShips;

int main()
{
    
    std::unique_ptr<Player> playerPtr = std::make_unique<Player>();
    /* std::set<std::pair<char, int>> secik{{'A',1},{'B',2},{'C',3}};
    std::set<Ship> ships;
    std::pair<char, int> parka{'B',2};
    ships.insert(secik);
    std::cout << "Ships set size:" << ships.size() << std::endl;

    std::set<std::pair<char, int>>::iterator it;
    for(const auto& ship : ships)
    {

        it = std::find(ship.getCoords().begin(), ship.getCoords().end(), parka);
        
        if(it != ship.getCoords().end()) //found
        { 
         std::cout<<"Found element\n";
        }
        else
        {
           std::cout<<"element NOT found\n";
        }
        
    }
    std::set<std::pair<char, int>> secik2{{'C',2},{'D',2},{'E',3}};
    std::pair<char, int> parka2{'B',8};
    ships.insert(secik2);

    std::cout << "Ships set size:" << ships.size() << std::endl;
    for(const auto& ship : ships)
    {

        it = std::find(ship.getCoords().begin(), ship.getCoords().end(), parka2);
        
        if(it != ship.getCoords().end()) //found
        { 
         std::cout<<"Found element\n";
        }
        
        
    }
    for(const auto& ship : ships)
    {
        for(auto& coord : ship.getCoords()) 
        {
            std::cout << coord.first<<coord.second<<' ';
        }
        std::cout << '\n';
    }
 */
    return 0;
}