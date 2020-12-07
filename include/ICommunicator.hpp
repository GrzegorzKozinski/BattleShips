#pragma once

#include <iostream>
#include <vector>

#include "Formatter.hpp"
#include "Ship.hpp"
#include "Board.hpp"


namespace BattleShips{
    
class ICommunicator
{

public:
    
    virtual ~ICommunicator() {};
    virtual void shipPlacementGuide(std::vector<Ship>& ships) =0;

};


} //namespace BattleShips