#ifndef WIRECONFIGURATION_HH
#define WIRECONFIGURATION_HH

#include <cstdint>

#include <unordered_map>
#include <unordered_set>

#include "engine/position.hh"

enum class WireWidth : uint8_t { W1 = '1' };
enum class WireSide : uint8_t { Top = 't', Bottom = 'b' };

struct WireConfiguration {
    WireWidth width;
    WireSide  side;
    Direction dir;
    bool      value = false;

    std::string serialize() const;
    static WireConfiguration deserialize(std::string const& str);

    bool operator==(WireConfiguration const& o) const { return width == o.width && side == o.side && dir == o.dir && value == o.value; }
};

template <>
struct std::hash<WireConfiguration> {
    std::size_t operator()(WireConfiguration const& wc) const noexcept {
        return ((((uint8_t) wc.dir) << 16) | (((uint8_t) wc.side) << 8) | (uint8_t) wc.width) << wc.value;
    }
};

using WireSet = std::unordered_set<WireConfiguration>;
using WireMap = std::unordered_map<Position, WireSet>;

#endif //WIRECONFIGURATION_HH
