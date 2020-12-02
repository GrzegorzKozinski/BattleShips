#include "../include/Ship.hpp"
#include "gtest/gtest.h"
using namespace BattleShips;

std::set<std::pair<char, int>>ship2set{
        {'A', 1},
        {'A', 2},
        {'A', 3}};

TEST(ShipTest, ShipCTor) 
    { 
        std::set<std::pair<char, int>> ship1set{
        {'C', 2},
        {'D', 2},
        {'E', 2},
        {'F', 2}};
        
        Ship ship1(ship1set);
        Ship ship2(ship2set);

        ASSERT_EQ(ship2.getCoords(), ship2set);
        ASSERT_EQ(ship1.getCoords(), ship1set);
    }
TEST(ShipTest, ShipIdSetter)
{
    Ship s(ship2set);
    s.setShipId(s.getShipId());
    const unsigned int id(2);
    std::cout<<"Ship id: " << s.getShipId() << std::endl;
    ASSERT_EQ(s.getShipId(), id);
}
