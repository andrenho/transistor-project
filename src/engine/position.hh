#ifndef POSITION_HH
#define POSITION_HH

#include <cstdint>
#include <memory>
#include <string>

#include "exceptions/deserializationerror.hh"

enum class Direction : uint8_t {
    N = 'N', S = 'S', W = 'W', E='E'
};

enum class Orientation: uint8_t { Horizontal, Vertical };

//---------------------------------------

struct Position {
    ssize_t x, y;

    std::string serialize() const { return std::to_string(x) + "," + std::to_string(y); }
    static Position deserialize(std::string const& str) {
        int find = str.find(',');
        if (find == std::string::npos) throw DeserializationError();
        return {
            .x = std::stoi(str.substr(0, find - 1)),
            .y = std::stoi(str.substr(find + 1))
        };
    }

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
};

template<>
struct std::hash<SubPosition> {
    std::size_t operator()(SubPosition const& sp) const noexcept
    {
        return (std::hash<Position>{}(sp.pos) << 1) ^ std::hash<Direction>{}(sp.dir);
    }
};

#endif //POSITION_HH
