#ifndef CIRCUIT_ICONS_HH
#define CIRCUIT_ICONS_HH

#include <cstdint>

enum class Sprite {
    Tile = 0,
    BoardTopLeft, BoardTop, BoardTopRight, BoardLeft, BoardRight, BoardBottomLeft, BoardBottom, BoardBottomRight,
    VCC, NPN, PNP, ButtonOff, ButtonOn, LedOff, LedOn,
    ShadowRect, ShadowSquare, ShadowCircle,
    WireTopOnNorth_1, WireTopOnEast_1, WireTopOnWest_1, WireTopOnSouth_1,
    WireTopOffNorth_1, WireTopOffEast_1, WireTopOffWest_1, WireTopOffSouth_1,
};

static constexpr uint8_t TILE_SIZE = 16;

constexpr struct {
    uint8_t x = 0;
    uint8_t y = 0;
    uint8_t w = 1;
    uint8_t h = 1;
} sprite_coordinates[] = {
    { 2, 2 },       // Tile
    { 0, 0, 2, 2 }, // Board*
    { 2, 0, 1, 2 },
    { 3, 0, 2, 2 },
    { 0, 2, 2, 1 },
    { 3, 2, 2, 1 },
    { 0, 3, 2, 2 },
    { 2, 3, 1, 2 },
    { 3, 3, 2, 2 },
    { 8, 2 },       // VCC
    { 5, 2 },
    { 5, 3 },
    { 6, 2 },
    { 6, 3 },
    { 7, 2 },
    { 7, 3 },
    { 5, 4 },       // Shadow*
    { 6, 4 },
    { 7, 4 },
    { 0, 7 }, { 1, 7 }, { 2, 7 }, { 3, 7 },  // WireTopOn*
    { 0, 5 }, { 1, 5 }, { 2, 5 }, { 3, 5 },  // WireTopOff*
};

#endif //CIRCUIT_ICONS_HH
