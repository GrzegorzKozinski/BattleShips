
#include <gtest/gtest.h>
#include "../src/Coordinate.hpp"
#include "../src/Player.cpp"
#include "../src/Ship.cpp"
#include <iostream>

using namespace BattleShips;

class TestPlayer : public ::testing::Test , private BattleShips::Player
{
protected:
    Player player;
};

TEST_F(TestPlayer, getShipOfSize3CoordsUserInputCheck)
{
    // Set up test input
    const std::istringstream input("A1\nA2\nA3\n");
    auto cin_backup = std::cin.rdbuf();
    const std::set<Coordinate> expectedCoords{Coordinate('A', 1), Coordinate('A', 2), Coordinate('A', 3)};
    

    std::cin.rdbuf(input.rdbuf());
    std::set<Coordinate> inputCoords{player.getNewShipCoords()};

    std::cin.rdbuf(cin_backup);
    ASSERT_EQ(inputCoords.size(), 3u);
    EXPECT_EQ(inputCoords, expectedCoords);
}

TEST_F(TestPlayer, getShipOfSize3CoordsUserInputCheckHorizontal)
{
    // Set up test input
    const std::istringstream input("B2\nC2\nD2\n");
    const std::set<Coordinate> expectedCoords{Coordinate('B', 2), Coordinate('C', 2), Coordinate('D', 2)};
    auto cin_backup = std::cin.rdbuf();

    std::cin.rdbuf(input.rdbuf());
    std::set<Coordinate> inputCoords{player.getNewShipCoords()};

    std::cin.rdbuf(cin_backup);
    ASSERT_EQ(inputCoords.size(), 3u);
    EXPECT_EQ(inputCoords, expectedCoords);
}
