#include "compiler.hh"

#include <iostream>


namespace compiler {

static std::unordered_set<Pin> find_all_pins(Board const& board)
{
    std::unordered_set<Pin> all_pins;
    for (auto const& [c_pos, component]: board.components()) {
        size_t i = 0;
        for (auto const& spos: component->pin_relative_positions()) {
            all_pins.emplace(component.get(), i, spos + c_pos);
            ++i;
        }
    }
    return all_pins;
}

static std::unordered_set<SubPosition> find_full_wire(Board const& board, SubPosition start, WireLayer wire_layer)
{
    std::unordered_set full_wire { start };
    std::unordered_set pending_for_evaluation { start };

    while (!pending_for_evaluation.empty()) {
        auto const& pending = *pending_for_evaluation.begin();

        for (auto const& sp: pending.connections()) {
            if (board.contains_wire(sp, wire_layer) && !full_wire.contains(sp)) {
                full_wire.emplace(sp);
                pending_for_evaluation.emplace(sp);
            }
        }

        pending_for_evaluation.erase(pending);
    }

    return full_wire;
}

static Connection find_connections(Sandbox const& sandbox, Pin const& starting_pin, std::unordered_set<Pin> const& pins, WireLayer wire_layer)
{
    Connection connection;
    connection.wire_layer = wire_layer;
    connection.pins.push_back(starting_pin);

    // begin with the staring pin
    auto current_spos = starting_pin.spos.connections();

    // add all possible

    return connection;
}

inline std::vector<Connection> compile(Sandbox const& sandbox)
{
    return {};
}

}