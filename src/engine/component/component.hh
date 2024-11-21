#ifndef COMPONENT_HH
#define COMPONENT_HH

#include <cstdint>
#include <variant>
#include <vector>

#include "ui/spritesheet.hh"

using ComponentImage = std::variant<std::vector<Sprite>>;

class Component {
public:
    virtual std::vector<uint8_t> simulate([[maybe_unused]] std::vector<uint8_t> const& inputs) = 0;
    virtual ComponentImage       component_image() const = 0;

    // TODO - serialization
    virtual ~Component() = default;

    struct ComponentType const* type;

protected:
    explicit Component(ComponentType const* component_type_) : type(component_type_) {}
};

#endif //COMPONENT_HH
