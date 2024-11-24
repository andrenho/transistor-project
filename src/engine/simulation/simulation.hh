#ifndef SIMULATION_HH
#define SIMULATION_HH

#include <vector>
#include <unordered_set>

#include "engine/component/component.hh"
#include "engine/toplevel/toplevel.hh"

class Simulation {
public:
    void compile(std::vector<std::unique_ptr<TopLevel>>& toplevels);
    void cycle();

    struct Pin {
        Component*  component;
        uint8_t     pin_no;
        SubPosition spos;
        bool operator==(Pin const& other) const { return other.component == component && other.pin_no == pin_no; }
    };

    struct Connection {
        std::vector<Pin>                pins;
        std::unordered_set<SubPosition> wires;
        bool                            value;
    };

private:
    std::vector<Connection> connections_;
};

template<>
struct std::hash<Simulation::Pin> {
    std::size_t operator()(Simulation::Pin const& pin) const noexcept {
        return (uintptr_t) pin.component ^ pin.pin_no;
    }
};

#endif //SIMULATION_HH
