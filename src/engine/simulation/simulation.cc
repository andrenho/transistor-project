#include "simulation.hh"

void Simulation::compile(std::vector<std::unique_ptr<TopLevel>>& toplevels)
{
    // find all pins
    std::unordered_set<Pin> all_pins;
    for (auto const& toplevel: toplevels) {
        for (auto const& [_, component]: toplevel->components()) {
            size_t i = 0;
            for (auto const& spos: component->pin_positions()) {
                all_pins.emplace(component.get(), i, spos);
                ++i;
            }
        }
    }

    // for each pin, follow the wire and create the connection
}

void Simulation::cycle()
{

}
