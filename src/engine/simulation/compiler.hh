#ifndef COMPILER_HH
#define COMPILER_HH
#include "simulation.hh"
#include "engine/sandbox.hh"


namespace compiler {

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

std::vector<Connection> compile(Sandbox const& sandbox);

}

namespace std {
    template<>
    struct hash<compiler::Pin> {
        size_t operator()(compiler::Pin const& pin) const noexcept {
            return (uintptr_t) pin.component ^ pin.pin_no;
        }
    };
}


#endif //COMPILER_HH
