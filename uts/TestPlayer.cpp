
#include <gtest/gtest.h>
#include "../src/Coordinate.hpp"
#include "../src/Player.cpp"
#include "../src/Ship.cpp"
#include <iostream>

using namespace BattleShips;

class TestPlayer : public ::testing::Test
{
protected:
    template <class T>
    void expectNeighbourFields(const T &placedFields, const std::set<Coordinate> &expectedSet) const
    {
        const std::set<Coordinate> result{player.getNextPossibleFields(placedFields)};
        EXPECT_EQ(result, expectedSet);
    }

    Player player;
    static constexpr char lastLetter{'A' + general::boardSize - 1};
    static constexpr int  lastDigit {general::boardSize};
    const Coordinate corner1{'A', 1}, corner2{lastLetter, 1} , corner3{lastLetter, lastDigit} , corner4{'A', lastDigit} ;
};

TEST_F(TestPlayer, getShipOfSize3CoordsUserInputCheck)
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

TEST_F(TestPlayer, getNextPossibleFields_2ndFieldWhenAllDirectionsFree) // expect calls after sorting methods as private and public
{
    expectNeighbourFields(Coordinate('B', 2), {Coordinate('B', 1), Coordinate('A', 2), Coordinate('B', 3), Coordinate('C', 2)});
}
// new possible fields are more like board responsibility?
TEST_F(TestPlayer, getNextPossibleFields_1stFieldIsCorner)
{
    expectNeighbourFields(corner1, {Coordinate('A', 2), Coordinate('B', 1)});
    expectNeighbourFields(corner2, {Coordinate(lastLetter - 1, 1), Coordinate(lastLetter, 2)});
    expectNeighbourFields(corner3, {Coordinate(lastLetter, lastDigit - 1), Coordinate(lastLetter - 1, lastDigit)});
    expectNeighbourFields(corner4, {Coordinate('A', lastDigit - 1), Coordinate('B', lastDigit)});
}

TEST_F(TestPlayer, getNextPossibleFields_1stFieldNearTheWall)
{
    expectNeighbourFields(Coordinate('A', 3), {Coordinate('A', 2), Coordinate('A', 4), Coordinate('B', 3)});
    expectNeighbourFields(Coordinate('C', 1), {Coordinate('B', 1), Coordinate('D', 1), Coordinate('C', 2)});
    expectNeighbourFields(Coordinate(lastLetter, 3), {Coordinate(lastLetter, 2), Coordinate(lastLetter, 4), Coordinate(lastLetter - 1, 3)});
    expectNeighbourFields(Coordinate('C', lastDigit), {Coordinate('B', lastDigit), Coordinate('D', lastDigit), Coordinate('C', lastDigit - 1)});
}

TEST_F(TestPlayer, getNextPossibleFields_2FieldsPlaced)
{
    const std::set<Coordinate> ship{Coordinate('C', 3), Coordinate('B', 3)};
    const std::set<Coordinate> expectedSet{Coordinate('A', 3), Coordinate('D', 3)};
    expectNeighbourFields(ship, expectedSet);
}

TEST_F(TestPlayer, getNextPossibleFields_2FieldsPlacedVertiacally)
{
    const std::set<Coordinate> ship{Coordinate('C', 3), Coordinate('C', 2)};
    const std::set<Coordinate> expectedSet{Coordinate('C', 1), Coordinate('C', 4)};
    expectNeighbourFields(ship, expectedSet);
}

TEST_F(TestPlayer, getNextPossibleFields_3FieldsPlaced)
{
    const std::set<Coordinate> ship{Coordinate('C', 3), Coordinate('B', 3), Coordinate('D', 3)};
    const std::set<Coordinate> expectedSet{Coordinate('A', 3), Coordinate('E', 3)};
    expectNeighbourFields(ship, expectedSet);
}

TEST_F(TestPlayer, getNextPossibleFields_3FieldsPlacedWithCorners)
{
    std::set<Coordinate> ship{corner1, Coordinate('A', 2), Coordinate('A', 3)};
    expectNeighbourFields(ship, {Coordinate('A', 4)});

    ship = {{corner1}, Coordinate('B', 1), Coordinate('C', 1)};
    expectNeighbourFields(ship, {Coordinate('D', 1)});

    ship = {corner3, Coordinate(lastLetter, lastDigit - 1), Coordinate(lastLetter, lastDigit - 2)};
    expectNeighbourFields(ship, {Coordinate(lastLetter, lastDigit - 3)});
}
