#ifndef POSITION_HH
#define POSITION_HH

#include <cstdint>
#include <memory>
#include <string>

#include "exceptions/deserializationerror.hh"

enum class Direction : uint8_t {
    N = 'N', S = 'S', W = 'W', E='E'
};

Direction rotate(Direction dir);

enum class Orientation: uint8_t { Horizontal, Vertical };

//---------------------------------------

struct Position {
    ssize_t x, y;

    std::string serialize() const;
    static Position deserialize(std::string const& str);

    bool operator==(Position const& other) const { return x == other.x && y == other.y; }
};

template<>
struct std::hash<Position> {
    std::size_t operator()(Position const& p) const noexcept
    {
        return (std::hash<ssize_t>{}(p.x) << 1) ^ std::hash<ssize_t>{}(p.y);
    }
};

//---------------------------------------

struct SubPosition {
    Position  pos;
    Direction dir;

    bool operator==(SubPosition const& other) const { return pos == other.pos && dir == other.dir; }
};

template<>
struct std::hash<SubPosition> {
    std::size_t operator()(SubPosition const& sp) const noexcept
    {
        return (std::hash<Position>{}(sp.pos) << 1) ^ std::hash<Direction>{}(sp.dir);
    }
};

#endif //POSITION_HH
