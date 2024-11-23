#ifndef SIMULATION_HH
#define SIMULATION_HH

#include <vector>

#include "engine/component/component.hh"
#include "engine/toplevel/toplevel.hh"

class Simulation {
public:
    void compile(std::vector<std::unique_ptr<TopLevel>>& toplevels);
    void cycle();

private:
};

#endif //SIMULATION_HH
