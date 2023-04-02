#include "Board.hpp"

#include <vector>
#include <iostream>
#include <memory>
#include <set>

namespace BattleShips
{

    Board::Board() 
    {
        clear();
        std::cout << "Board constructed \n";
    }

    Board::~Board()
    {
        std::cout << "Board destroyed \n";
    }

    Fields Board::getFields() const
    {
        return fields_;
    }

    void Board::clear()
    {
        for (uint64_t col{0}; col < fields_.size(); ++col)
        {
            fields_[col].fill(EField::EMPTY); // fill board with empty fields
        }
    }

    EField Board::getField(const Coordinate &coordinate) const
    {
        const auto idx{coordinate.getIndices()};
        printf("getField: letterIdx is %d digitIdx is %d \n", idx.first, idx.second);
        return fields_[idx.first][idx.second]; // to test thiws method
    }

    EField& Board::getFieldRef(const Coordinate &coordinate) const
    {
        const auto idx{coordinate.getIndices()};
        return fields_[idx.first][idx.second];
    }

    void Board::printBoard() const // pretty print board
    {
        settings_.printHeader();
        for (uint64_t i = 0; i < fields_.size(); ++i)
        {
            std::cout << i + 1 << " | ";
            for (uint64_t j = 0; j < fields_.at(0).size(); ++j)
            {
                std::cout << fields_.at(j).at(i) << " | ";
            }
            GlobalSettings::print_dashed_row();
        }
    }

} // namespace BattleShips