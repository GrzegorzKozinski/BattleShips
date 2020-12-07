#pragma once

#include <iostream>
#include <memory>


#include "Board.hpp"


namespace BattleShips{


class AiCommunicator : public ICommunicator
{

public:
    AiCommunicator();
    ~AiCommunicator();
};
} // namespace BattleShips

