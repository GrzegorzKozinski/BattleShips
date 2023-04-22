#pragma once

namespace general{
    static constexpr int asciiIntToChar{65};
    static constexpr uint64_t boardSize{6};
    static constexpr uint8_t numOfShipsPerPlayer{2};
    static constexpr std::array<uint8_t, numOfShipsPerPlayer> shipSizes{3, 3}; // ship size and count 
    static constexpr int asciiCharToInt{48};
}//namespace const