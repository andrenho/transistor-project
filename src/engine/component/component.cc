#include "component.hh"

#include <vector>

#include "vcc.hh"

std::vector<ComponentType*> default_component_types = {
    VCC::component_type(),
};