#ifndef VCC_HH
#define VCC_HH

#include "component.hh"

struct VCC : Component {

    explicit VCC(ComponentType const* ct) : Component(ct) {}

    std::vector<uint8_t> simulate([[maybe_unused]] std::vector<uint8_t> const& inputs) override
    {
        return { 1 };
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
            .component_image = std::vector<Sprite> { Sprite::ShadowSquare, Sprite::VCC },
        };
        vcc.create_component = [&]() { return std::make_unique<VCC>(&vcc); };
        return &vcc;
    }
};


#endif //VCC_HH
