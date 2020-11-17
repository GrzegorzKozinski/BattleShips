#pragma once

#include <iostream>
#include <vector>

#include "Ship.hpp"

namespace BattleShips{
class ICommunicator
{


    
public:
    virtual ~ICommunicator() {};
    virtual void shipPlacementGuide(std::vector<Ship>& ships) =0;

};


} //namespace BattleShips