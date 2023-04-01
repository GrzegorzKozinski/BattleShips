
#include <gtest/gtest.h>
#include "../src/Coordinate.hpp"
#include "../src/Player.cpp"
#include "../src/Ship.cpp"
#include <iostream>

using namespace BattleShips;

class TestPlayer : public ::testing::Test
{
protected:
    void expectNeighbourFieldsWhen1stFieldPlaced(const Coordinate &firstField, const std::set<Coordinate> &expectedSet) const
    {
        const std::set<Coordinate> result{player.getNextPossibleFields(firstField)};
        EXPECT_EQ(expectedSet.size(), result.size());
        EXPECT_EQ(result, expectedSet);
    }
    Player player;
    static constexpr char lastLetter{'A' + general::boardSize - 1};
    static constexpr int lastDigit{general::boardSize};
    
};

TEST_F(TestPlayer, getNewShipCoordsUserInputCheck)
{
    // Set up test input
    const std::istringstream input("A1\nA2\nA3\n");
    const std::set<Coordinate> expectedCoords{Coordinate('A', 1), Coordinate('A', 2), Coordinate('A', 3)};
    auto cin_backup = std::cin.rdbuf();
    std::cin.rdbuf(input.rdbuf());

    std::set<Coordinate> inputCoords{player.getNewShipCoords()};
    std::cin.rdbuf(cin_backup);

    ASSERT_EQ(inputCoords.size(), 3u);
    EXPECT_EQ(inputCoords, expectedCoords);
}

TEST_F(TestPlayer, getNextPossibleFields_2ndFieldWhenAllDirectionsFree) // expect calls after sorting methods as private and public
{
    expectNeighbourFieldsWhen1stFieldPlaced(Coordinate('B', 2), {Coordinate('B', 1), Coordinate('A', 2), Coordinate('B', 3), Coordinate('C', 2)});
}
// new possible fields are more like board responsibility?
TEST_F(TestPlayer, getNextPossibleFields_1stFieldIsCorner)
{
    expectNeighbourFieldsWhen1stFieldPlaced(Coordinate('A', 1), {Coordinate('A', 2), Coordinate('B', 1)});
    expectNeighbourFieldsWhen1stFieldPlaced(Coordinate(lastLetter, 1), {Coordinate(lastLetter - 1, 1), Coordinate(lastLetter, 2)});
    expectNeighbourFieldsWhen1stFieldPlaced(Coordinate(lastLetter, lastDigit), {Coordinate(lastLetter, lastDigit - 1), Coordinate(lastLetter - 1, lastDigit)});
    expectNeighbourFieldsWhen1stFieldPlaced(Coordinate('A', lastDigit), {Coordinate('A', lastDigit - 1), Coordinate('B', lastDigit)});
}

TEST_F(TestPlayer, getNextPossibleFields_1stFieldNearTheWall)
{
    expectNeighbourFieldsWhen1stFieldPlaced(Coordinate('A', 3), {Coordinate('A', 2), Coordinate('A', 4), Coordinate('B', 3)});
    expectNeighbourFieldsWhen1stFieldPlaced(Coordinate('C', 1), {Coordinate('B', 1), Coordinate('D', 1), Coordinate('C', 2)});
    expectNeighbourFieldsWhen1stFieldPlaced(Coordinate(lastLetter, 3), {Coordinate(lastLetter, 2), Coordinate(lastLetter, 4), Coordinate(lastLetter-1, 3)});
    expectNeighbourFieldsWhen1stFieldPlaced(Coordinate('C', lastDigit), {Coordinate('B', lastDigit), Coordinate('D', lastDigit), Coordinate('C', 4)});
}