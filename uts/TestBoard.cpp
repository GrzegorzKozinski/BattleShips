#include "../src/Board.cpp"
#include "../src/Board.hpp"
#include "../src/Coordinate.hpp"
#include "../src/EField.hpp"
#include "../src/GlobalSettings.cpp"
#include "../src/GlobalSettings.hpp"
#include <gtest/gtest.h>

using namespace BattleShips;

class TestBoard : public ::testing::Test
{
protected:
    Board board;
    template <class T>
    void expectNeighbourFields(const T& placedFields, const std::set<Coordinate>& expectedSet)
    {
        const std::set<Coordinate> result{board.getNeighbourFields(placedFields)};
        EXPECT_EQ(result, expectedSet);
    }
    bool allFieldsEqual(const std::set<Coordinate> coords, const EField field) const
    {
        return std::all_of(coords.begin(), coords.end(),
                           [&](const Coordinate& coordinate)
                           { return board.getField(coordinate) == field; });
    }
    static constexpr char lastLetter{'A' + general::boardSize - 1};
    static constexpr int lastDigit{general::boardSize};
    const Coordinate corner1{'A', 1}, corner2{lastLetter, 1},
        corner3{lastLetter, lastDigit}, corner4{'A', lastDigit};
};

TEST_F(TestBoard, BoardConstructedAllWithEmptyFields)
{
    Board freshBoard{};
    const auto allFiledsEmpty = [](const auto& row)
    {
        return std::all_of(row.begin(), row.end(),
                           [](const auto& field)
                           { return field == EField::EMPTY; });
    };

    const bool allRowsFilledWithEmptyFields = std::all_of(freshBoard.getFields().cbegin(), freshBoard.getFields().cend(), allFiledsEmpty);
    EXPECT_TRUE(allRowsFilledWithEmptyFields);
}

TEST_F(TestBoard, GetFieldReturnsCorrectField)
{
    const BattleShips::Coordinate coordinate('A', 1);
    const EField expectedField = EField::EMPTY;

    EField& actualField = board.getFieldRef(coordinate);
    EXPECT_EQ(actualField, expectedField);
}

TEST_F(TestBoard, setFieldPutsChosenFieldTypeOnGivenCoordinate)
{
    board.clear();
    const Coordinate expectedShipCoordinate{'A', 1};
    const Coordinate expectedMissCoordinate{'B', 1};
    const Coordinate expectedHitsCoordinate{'A', 2};
    const Coordinate expectedEmptyCoordinate{'A', 1};

    board.setField(expectedShipCoordinate, EField::SHIP);
    board.setField(expectedMissCoordinate, EField::MISSED);
    board.setField(expectedHitsCoordinate, EField::HIT);

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
                                                          [&](const Coordinate& coordinate)
                                                          { return board.getField(coordinate) == EField::SHIP; })};
    EXPECT_TRUE(allFieldsAtCoordsHaveStateShip);
}

TEST_F(TestBoard, surroundShipsWithMissFieldsSetsAllNeighbourFieldsAsMissed)
{
    board.clear();
    const std::set<Coordinate> shipCoords{Coordinate('A', 1), Coordinate('A', 2), Coordinate('A', 3)};
    // [ B1, B2, B3, A4 ] is surruonding it
    const std::set<Coordinate> surroundingFields{Coordinate('B', 1), Coordinate('B', 2), Coordinate('B', 3), Coordinate('A', 4)};
    board.surroundShipsWithMissFields(shipCoords);

    EXPECT_TRUE(allFieldsEqual(surroundingFields, EField::MISSED));
}

TEST_F(TestBoard, getNextPossibleFields_2ndFieldWhenAllDirectionsFree) // expect calls after sorting methods as private and public
{
    expectNeighbourFields(Coordinate('B', 2), {Coordinate('B', 1), Coordinate('A', 2), Coordinate('B', 3), Coordinate('C', 2)});
}
// new possible fields are more like board responsibility?
TEST_F(TestBoard, getNextPossibleFields_1stFieldIsCorner)
{
    expectNeighbourFields(corner1, {Coordinate('A', 2), Coordinate('B', 1)});
    expectNeighbourFields(corner2, {Coordinate(lastLetter - 1, 1), Coordinate(lastLetter, 2)});
    expectNeighbourFields(corner3, {Coordinate(lastLetter, lastDigit - 1), Coordinate(lastLetter - 1, lastDigit)});
    expectNeighbourFields(corner4, {Coordinate('A', lastDigit - 1), Coordinate('B', lastDigit)});
}

TEST_F(TestBoard, getNextPossibleFields_1stFieldNearTheWall)
{
    expectNeighbourFields(Coordinate('A', 3), {Coordinate('A', 2), Coordinate('A', 4), Coordinate('B', 3)});
    expectNeighbourFields(Coordinate('C', 1), {Coordinate('B', 1), Coordinate('D', 1), Coordinate('C', 2)});
    expectNeighbourFields(Coordinate(lastLetter, 3), {Coordinate(lastLetter, 2), Coordinate(lastLetter, 4), Coordinate(lastLetter - 1, 3)});
    expectNeighbourFields(Coordinate('C', lastDigit), {Coordinate('B', lastDigit), Coordinate('D', lastDigit), Coordinate('C', lastDigit - 1)});
}

TEST_F(TestBoard, getNextPossibleFields_2FieldsPlaced)
{
    const std::set<Coordinate> ship{Coordinate('C', 3), Coordinate('B', 3)};
    const std::set<Coordinate> expectedSet{Coordinate('A', 3), Coordinate('D', 3)};
    expectNeighbourFields(ship, expectedSet);
}

TEST_F(TestBoard, getNextPossibleFields_2FieldsPlacedVertiacally)
{
    const std::set<Coordinate> ship{Coordinate('C', 3), Coordinate('C', 2)};
    const std::set<Coordinate> expectedSet{Coordinate('C', 1), Coordinate('C', 4)};
    expectNeighbourFields(ship, expectedSet);
}

TEST_F(TestBoard, getNextPossibleFields_3FieldsPlaced)
{
    const std::set<Coordinate> ship{Coordinate('C', 3), Coordinate('B', 3), Coordinate('D', 3)};
    const std::set<Coordinate> expectedSet{Coordinate('A', 3), Coordinate('E', 3)};
    expectNeighbourFields(ship, expectedSet);
}

TEST_F(TestBoard, getNextPossibleFields_3FieldsPlacedWithCorners)
{
    std::set<Coordinate> ship{corner1, Coordinate('A', 2), Coordinate('A', 3)};
    expectNeighbourFields(ship, {Coordinate('A', 4)});

    ship = {{corner1}, Coordinate('B', 1), Coordinate('C', 1)};
    expectNeighbourFields(ship, {Coordinate('D', 1)});

    ship = {corner3, Coordinate(lastLetter, lastDigit - 1), Coordinate(lastLetter, lastDigit - 2)};
    expectNeighbourFields(ship, {Coordinate(lastLetter, lastDigit - 3)});
}
