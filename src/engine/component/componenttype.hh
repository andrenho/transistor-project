#ifndef COMPONENTTYPE_HH_
#define COMPONENTTYPE_HH_

#include <functional>
#include <variant>
#include <vector>

#include "component.hh"
#include "engine/position.hh"

enum PinType { Input, Output, InputOutput };

struct Pin {
    std::variant<Position, SubPosition> pos;
    PinType                             type;
};

struct PhysicalCharacteristics {
    uint8_t          size_w = 1;
    uint8_t          size_h = 1;
    bool             can_rotate;
    std::vector<Pin> pins;
};

struct ComponentType {
    std::string              id;
    PhysicalCharacteristics  physical_characteristics;
    std::optional<uint32_t>  key_to_place;

    std::function<std::unique_ptr<Component>()> create_component = nullptr;
};

extern std::vector<ComponentType*> default_component_types;

#endif