#include "component.hh"

#include <vector>

#include "led.hh"
#include "vcc.hh"

std::vector<ComponentType*> default_component_types = {
    VCC::component_type(),
    LED::component_type()
};