#include "compiler.hh"

namespace compiler {

static std::unordered_set<Pin> find_all_pins(Sandbox const& sandbox)
{
    std::unordered_set<Pin> all_pins;
    for (auto const& toplevel: sandbox.toplevels()) {
        for (auto const& [c_pos, component]: toplevel->components()) {
            size_t i = 0;
            for (auto const& spos: component->pin_relative_positions()) {
                all_pins.emplace(component.get(), i, spos + c_pos);
                ++i;
            }
        }
    }
    return all_pins;
}

static Connection find_connections(Pin const& pin, std::unordered_set<Pin> const& pins)
{
    Connection connection;

    return connection;
}

std::vector<Connection> compile(Sandbox const& sandbox)
{
    return {};
}

}