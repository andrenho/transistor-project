#ifndef SIMULATION_HH
#define SIMULATION_HH

#include <vector>

#include "engine/toplevel/toplevel.hh"

class Simulation {
public:
    void compile(std::vector<std::unique_ptr<TopLevel>>& toplevels);
    void cycle();
};

#endif //SIMULATION_HH
