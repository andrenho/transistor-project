#include "compiler.hh"

namespace compiler {

static std::unordered_set<Pin> find_all_pins(Sandbox const& sandbox)
{
    std::unordered_set<Pin> all_pins;
    for (auto const& toplevel: sandbox.toplevels()) {
        for (auto const& [_, component]: toplevel->components()) {
            size_t i = 0;
            for (auto const& spos: component->pin_positions()) {
                all_pins.emplace(component.get(), i, spos);
                ++i;
            }
        }
    }
    return all_pins;
}

std::vector<Connection> compile(Sandbox const& sandbox)
{
    return {};
}

}