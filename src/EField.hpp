#pragma once
#include <ostream>
namespace BattleShips{

enum class EField
{
    EMPTY , 
    SHIP ,
    HIT ,
    MISSED
}; 

inline std::ostream& operator<<(std::ostream& out, const EField& e) 
{
    switch(e) {
        case EField::EMPTY:
            out << ' '; 
            break;
        case EField::SHIP:
            out << 'S';
            break;
        case EField::HIT:
            out << 'X';
            break;
        case EField::MISSED:
            out << 'O';
            break;
        default:
            break;
    }
    return out;
}
}