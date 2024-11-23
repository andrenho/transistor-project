#ifndef COMPONENTTYPE_HH_
#define COMPONENTTYPE_HH_

#include <functional>
#include <optional>
#include <variant>
#include <vector>

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

class Component;

struct ComponentType {
    std::string              id;
    PhysicalCharacteristics  physical_characteristics;
    std::optional<uint32_t>  key_to_place;

    std::function<std::unique_ptr<Component>()>                   create_component = nullptr;
    std::function<std::unique_ptr<Component>(std::string const&)> create_component_from_serial = nullptr;
};

#define COMPONENT_CONSTRUCTOR(klass) explicit klass (ComponentType const* ct) : Component(ct) {}
#define COMPONENT_TYPE_INIT(klass, var) { \
    var.create_component = [&]() { return std::make_unique<klass>(&var); }; \
    var.create_component_from_serial = [&](std::string const& serial) { return std::make_unique<klass>(&var, serial); }; \
}

extern std::vector<ComponentType*> default_component_types;

#endif