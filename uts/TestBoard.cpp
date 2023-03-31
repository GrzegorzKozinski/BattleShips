#include <gtest/gtest.h>
#include "../src/Board.cpp"
#include "../src/Board.hpp"
#include "../src/Coordinate.hpp"
#include "../src/GlobalSettings.cpp"
#include "../src/GlobalSettings.hpp"
#include "../src/EField.hpp"

using namespace BattleShips;

class TestBoard : public ::testing::Test
{
protected:
    Board board;
};

TEST_F(TestBoard, BoardConstructedAllWithEmptyFields)
{
    Board freshBoard{};
    const auto allFiledsEmpty = [](const auto &row)
    {
        return std::all_of(row.begin(), row.end(),
                           [](const auto &field)
                           { return field == EField::EMPTY; });
    };

    const bool allRowsFilledWithEmptyFields = std::all_of(freshBoard.getFields().cbegin(), freshBoard.getFields().cend(), allFiledsEmpty);
    EXPECT_TRUE(allRowsFilledWithEmptyFields);
}

TEST_F(TestBoard, GetFieldReturnsCorrectField)
{
    const BattleShips::Coordinate coordinate('A', 1);
    const EField expectedField = EField::EMPTY;

    EField &actualField = board.getFieldRef(coordinate);
    EXPECT_EQ(actualField, expectedField);
}

TEST_F(TestBoard, setFieldPutsChosenFieldTypeOnGivenCoordinate)
{
    board.clear();
    const Coordinate expectedShipCoordinate {'A', 1};
    const Coordinate expectedMissCoordinate {'B', 1};
    const Coordinate expectedHitsCoordinate {'A', 2};
    const Coordinate expectedEmptyCoordinate{'A', 1};

    board.setField(expectedShipCoordinate,  EField::SHIP);
    board.setField(expectedMissCoordinate,  EField::MISSED);
    board.setField(expectedHitsCoordinate,  EField::HIT);

    EXPECT_EQ(board.getField(expectedShipCoordinate), EField::SHIP);
    EXPECT_EQ(board.getField(expectedMissCoordinate), EField::MISSED);
    EXPECT_EQ(board.getField(expectedHitsCoordinate), EField::HIT);

    board.setField(expectedEmptyCoordinate, EField::EMPTY); // set A1 back to EmptyState
    EXPECT_EQ(board.getField(expectedEmptyCoordinate), EField::EMPTY);
}

TEST_F(TestBoard, markNewShipPositionSetsGivenCoordinatesAsShip)
{
    board.clear();

    const std::set<Coordinate> incomingCoords{Coordinate('A', 1), Coordinate('B', 2), Coordinate('D', 5)};
    board.markNewShipPosition(incomingCoords);
    board.printBoard();
    const bool allFieldsAtCoordsHaveStateShip{std::all_of(incomingCoords.begin(), incomingCoords.end(),
         [&](const Coordinate& c) { return board.getField(c) == EField::SHIP;})};
    EXPECT_TRUE(allFieldsAtCoordsHaveStateShip);
}