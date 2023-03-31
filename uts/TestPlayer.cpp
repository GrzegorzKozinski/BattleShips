
#include <gtest/gtest.h>
#include "../src/Coordinate.hpp"
#include "../src/Player.cpp"
#include "../src/Ship.cpp"
#include <iostream>

using namespace BattleShips;

class TestPlayer : public ::testing::Test 
{
protected:
    Player player;
};


TEST_F(TestPlayer, getNewShipCoordsUserInputCheck) 
{
    // Set up test input
    const std::istringstream input("A1\nA2\nA3\n");
    const std::set<Coordinate> expectedCoords{Coordinate('A', 1), Coordinate('A', 2), Coordinate('A', 3)};
    auto cin_backup = std::cin.rdbuf();
    std::cin.rdbuf(input.rdbuf());

    std::set<Coordinate> inputCoords { player.getNewShipCoords() };
    std::cin.rdbuf(cin_backup);

    ASSERT_EQ(inputCoords.size(), 3u);
    EXPECT_EQ(inputCoords, expectedCoords);
}

TEST_F(TestPlayer, getNextPossibleFields_2ndFieldWhenAllDirectionsFree) // expect calls after sorting methods as private and public
{
    const Coordinate firstCoord('B', 2);
    const uint64_t setSizeWhenAllDirectionsFree{4};
    const std::set<Coordinate> expectedSet{Coordinate('B', 1), Coordinate('A', 2), Coordinate('B', 3), Coordinate('C', 2)};
    const std::set<Coordinate> result {player.getNextPossibleFields(firstCoord)};
    EXPECT_TRUE(result.size() == setSizeWhenAllDirectionsFree);
    EXPECT_EQ(result, expectedSet);
}

TEST_F(TestPlayer, getNextPossibleFields_1stFieldIsCorner) // extract some corner check for DRY rule 
                                                           // new possible fields are more like board responsibility
{
    Coordinate firstCoord('A', 1);
    std::set<Coordinate> expectedSet{Coordinate('A', 2), Coordinate('B', 1)};
    const uint64_t sizeWhen1stFieldPlacedInCorner{2};

    std::set<Coordinate> result {player.getNextPossibleFields(firstCoord)};
    ASSERT_TRUE(result.size() == sizeWhen1stFieldPlacedInCorner);
    EXPECT_EQ(result, expectedSet);

    firstCoord.letter = player.settings_.lastLetter();
    
    std::set<Coordinate> expectedSet2{Coordinate('D', 1), Coordinate('E', 2)};
    result = player.getNextPossibleFields(firstCoord);

    ASSERT_TRUE(result.size() == sizeWhen1stFieldPlacedInCorner);
    EXPECT_EQ(result, expectedSet2);

    firstCoord.digit = general::boardSize;
    
    std::cout << firstCoord << std::endl;
    const std::set<Coordinate> expectedSet3{Coordinate('E', 4), Coordinate('D', 5)};
    result = player.getNextPossibleFields(firstCoord);
   
    EXPECT_EQ(result, expectedSet3);
    ASSERT_TRUE(result.size() == sizeWhen1stFieldPlacedInCorner);

    firstCoord.letter = 'A';

    const std::set<Coordinate> expectedSet4{Coordinate('A', 4), Coordinate('B', 5)};
    result = player.getNextPossibleFields(firstCoord);
   
    EXPECT_EQ(result, expectedSet4);
    ASSERT_TRUE(result.size() == sizeWhen1stFieldPlacedInCorner);
}
