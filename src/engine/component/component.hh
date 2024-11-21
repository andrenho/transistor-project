#ifndef COMPONENT_HH
#define COMPONENT_HH

#include <cstdint>
#include <functional>
#include <variant>
#include <vector>

#include "engine/position.hh"
#include "ui/spritesheet.hh"

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

using ComponentImage = std::variant<std::vector<Sprite>>;

class Component {
public:
    virtual std::vector<uint8_t> simulate([[maybe_unused]] std::vector<uint8_t> const& inputs) = 0;
    // TODO - serialization
    virtual ~Component() = default;

    struct ComponentType const* component_type;

protected:
    explicit Component(ComponentType const* component_type_) : component_type(component_type_) {}
};

struct ComponentType {
    std::string              id;
    PhysicalCharacteristics  physical_characteristics;
    std::optional<uint32_t>  key_to_place;
    ComponentImage           component_image;   // TODO - transform this in function

    std::function<std::unique_ptr<Component>()> create_component = nullptr;
};

extern std::vector<ComponentType*> default_component_types;

#endif //COMPONENT_HH
