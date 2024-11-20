#include "components.hh"

std::vector<ComponentType> default_component_types()
{
    static std::vector<ComponentType> components = {

        // VCC
        ComponentType {
            .id = "vcc",
            .physical_characteristics = {
                .can_rotate = false,
                .inputs = {},
                .outputs = { { .pos = Position { 0, 0 } } },
            },
            .key_to_place = 'v',
            .component_image = { std::vector<Sprite> { Sprite::ShadowSquare, Sprite::VCC } },
            .create_component = []() { return std::make_unique<VCC>(); },
        },

    };
    return components;
}
