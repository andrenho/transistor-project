#ifndef SUBPOSITION_HH
#define SUBPOSITION_HH

#include <array>
#include <ostream>

#include "direction.hh"
#include "position.hh"

struct SubPosition {
    Position  pos;
    Direction dir;

    bool        operator==(SubPosition const& other) const { return pos == other.pos && dir == other.dir; }
    SubPosition operator+(Position const& o_pos) const { return { pos + o_pos, dir }; }

    constexpr std::array<SubPosition, 4> connections() const;
};

template<>
struct std::hash<SubPosition> {
    std::size_t operator()(SubPosition const& sp) const noexcept
    {
        return (std::hash<Position>{}(sp.pos) << 1) ^ std::hash<Direction>{}(sp.dir);
    }
};

inline std::ostream& operator<<(std::ostream& os, SubPosition const& sp) {
    return os << sp.pos << sp.dir;
}

constexpr std::array<SubPosition, 4> SubPosition::connections() const
{
    switch (dir) {
        case Direction::W:
            return {{
                { .pos = { pos.x - 1, pos.y }, .dir = Direction::E },
                { .pos = { pos.x, pos.y }, .dir = Direction::E },
                { .pos = { pos.x, pos.y }, .dir = Direction::N },
                { .pos = { pos.x, pos.y }, .dir = Direction::S },
            }};
        case Direction::E:
            return {{
                { .pos = { pos.x + 1, pos.y }, .dir = Direction::W },
                { .pos = { pos.x, pos.y }, .dir = Direction::W },
                { .pos = { pos.x, pos.y }, .dir = Direction::N },
                { .pos = { pos.x, pos.y }, .dir = Direction::S },
            }};
        case Direction::N:
            return {{
                { .pos = { pos.x, pos.y - 1 }, .dir = Direction::S },
                { .pos = { pos.x, pos.y }, .dir = Direction::S },
                { .pos = { pos.x, pos.y }, .dir = Direction::W },
                { .pos = { pos.x, pos.y }, .dir = Direction::E }
            }};
        case Direction::S:
            return {{
                { .pos = { pos.x, pos.y + 1 }, .dir = Direction::N },
                { .pos = { pos.x, pos.y }, .dir = Direction::S },
                { .pos = { pos.x, pos.y }, .dir = Direction::W },
                { .pos = { pos.x, pos.y }, .dir = Direction::E },
            }};
    }

    throw std::runtime_error("Invalid direction");
}

#endif //SUBPOSITION_HH
