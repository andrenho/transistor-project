#ifndef LED_HH
#define LED_HH

#include "component.hh"

struct LED : Component {

    explicit LED(ComponentType const* ct) : Component(ct) {}

    std::vector<uint8_t> simulate([[maybe_unused]] std::vector<uint8_t> const& inputs) override
    {
        value_ = inputs.at(0) || inputs.at(1) || inputs.at(2) || inputs.at(3);
        return {};
    }

    ComponentImage component_image() const override
    {
        return std::vector { Sprite::ShadowCircle, value_ ? Sprite::LedOn : Sprite::LedOff };
    }

    static ComponentType* component_type()
    {
        static auto led = ComponentType {
            .id = "led",
            .physical_characteristics = {
                .can_rotate = false,
                .pins = {
                    { .pos = Position { 0, 0 }, .type = Input }
                },
            },
            .key_to_place = 'l',
        };
        led.create_component = [&]() { return std::make_unique<LED>(&led); };
        return &led;
    }

private:
    bool value_ = false;
};



#endif //LED_HH
