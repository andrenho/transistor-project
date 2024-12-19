#ifndef POSITION_HH
#define POSITION_HH

#include <ostream>
#include <memory>
#include <string>

struct Position {
    ssize_t x, y;

    std::string serialize() const;
    static Position deserialize(std::string const& str);

    Position operator+(Position const& p) const { return { x + p.x, y + p.y }; }
    bool operator==(Position const& other) const { return x == other.x && y == other.y; }
};

template<>
struct std::hash<Position> {
    std::size_t operator()(Position const& p) const noexcept
    {
        return (std::hash<ssize_t>{}(p.x) << 1) ^ std::hash<ssize_t>{}(p.y);
    }
};

inline std::ostream& operator<<(std::ostream& os, Position const& pos) {
    return os << "<" << pos.x << "," << pos.y << ">";
}

#endif //POSITION_HH
