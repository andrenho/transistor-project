#ifndef Button_HH
#define Button_HH

#include "component.hh"

struct Button : Component {

    explicit Button(ComponentType const* ct) : Component(ct) {}

    std::vector<uint8_t> simulate([[maybe_unused]] std::vector<uint8_t> const& inputs) override
    {
        return { value_, value_, value_, value_ };
    }

    [[nodiscard]] ComponentImage component_image() const override
    {
        return std::vector { Sprite::ShadowSquare, value_ ? Sprite::ButtonOn : Sprite::ButtonOff };
    }

    static ComponentType* component_type()
    {
        static auto button = ComponentType {
            .id = "button",
            .physical_characteristics = {
                .can_rotate = false,
                .pins = {
                    { .pos = Position { 0, 0 }, .type = Output }
                },
            },
            .key_to_place = 'b',
        };
        button.create_component = [&]() { return std::make_unique<Button>(&button); };
        return &button;
    }

private:
    bool value_ = false;
};


#endif //Button_HH
