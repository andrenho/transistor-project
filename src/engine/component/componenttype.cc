#include "componenttype.hh"

#include <vector>

#include "button.hh"
#include "led.hh"
#include "vcc.hh"

std::vector<ComponentType*> default_component_types = {
    VCC::component_type(),
    LED::component_type(),
    Button::component_type(),
};