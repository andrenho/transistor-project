#ifndef VCC_HH
#define VCC_HH

#include "component.hh"

struct VCC : Component {

    COMPONENT_CONSTRUCTOR(VCC)

    VCC(ComponentType* ct, std::string const& serial) : VCC(ct) {}

    std::vector<uint8_t> simulate([[maybe_unused]] std::vector<uint8_t> const& inputs) override
    {
        return { 1 };
    }

    ComponentImage component_image() const override
    {
        return std::vector<ComponentSprite> {
            { Sprite::ShadowSquare, 1, 1 },
            { Sprite::VCC }
        };
    }

    static ComponentType* component_type()
    {
        static auto vcc = ComponentType {
            .id = "vcc",
            .physical_characteristics = {
                .can_rotate = false,
                .pins = {
                    { .pos = Position { 0, 0 }, .type = Output }
                },
            },
            .key_to_place = 'v',
        };
        COMPONENT_TYPE_INIT(VCC, vcc)
        return &vcc;
    }

protected:
    std::string serialize_component() const override { return ""; }
};


#endif //VCC_HH
