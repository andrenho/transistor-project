#ifndef COMPONENT_HH
#define COMPONENT_HH

#include <cstdint>
#include <string>
#include <variant>
#include <vector>

#include "componenttype.hh"
#include "ui/spritesheet.hh"

struct ComponentSprite {
    Sprite sprite;
    int displacement_x = 0, displacement_y = 0;
};

using ComponentImage = std::variant<std::vector<ComponentSprite>>;

class Component {
public:
    virtual std::vector<uint8_t> simulate([[maybe_unused]] std::vector<uint8_t> const& inputs) = 0;
    virtual void                 on_click([[maybe_unused]] size_t x, [[maybe_unused]] size_t y) {}

    virtual ComponentImage  component_image() const = 0;

    void                    rotate() { if (type->physical_characteristics.can_rotate) direction_ = ::rotate(direction_); }

    std::string             serialize() const { return type->id + ":" + serialize_component(); }
    [[nodiscard]] Direction direction() const { return direction_; }

    std::vector<SubPosition> pin_positions() const;

    virtual ~Component() = default;

    ComponentType const* type;

    static std::unique_ptr<Component> deserialize(std::vector<ComponentType*> const& supported_component_types,
        std::string const& serial);

protected:
    Direction direction_ = Direction::N;

    explicit Component(ComponentType const* component_type_) : type(component_type_) {}

    virtual std::string serialize_component() const = 0;
};

#endif //COMPONENT_HH
