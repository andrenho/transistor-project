#ifndef COMPONENTS_HH
#define COMPONENTS_HH

#include "component.hh"

struct VCC : Component {
    std::vector<uint8_t> simulate([[maybe_unused]] std::vector<uint8_t> const& inputs) override
    {
        return { 1 };
    }
};

std::vector<ComponentType> default_component_types();

#endif //COMPONENTS_HH
