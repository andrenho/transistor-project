#ifndef COMPONENT_HH
#define COMPONENT_HH

#include <cstdint>
#include <functional>
#include <variant>
#include <vector>

#include "engine/position.hh"
#include "ui/spritesheet.hh"

struct Pin {
    std::variant<Position, SubPosition> pos;
};

struct PhysicalCharacteristics {
    uint8_t          size_w = 1;
    uint8_t          size_h = 1;
    bool             can_rotate;
    std::vector<Pin> inputs;
    std::vector<Pin> outputs;
};

struct ComponentImage {
    std::variant<std::vector<Sprite>> image;
};

class Component {
public:
    virtual std::vector<uint8_t> simulate([[maybe_unused]] std::vector<uint8_t> const& inputs) = 0;
    // TODO - serialization
    virtual ~Component() = default;
protected:
    Component() = default;
};

struct ComponentType {
    std::string              id;
    PhysicalCharacteristics  physical_characteristics;
    std::optional<uint32_t>  key_to_place;
    ComponentImage           component_image;

    std::function<std::unique_ptr<Component>()> create_component;
};

#endif //COMPONENT_HH
