#ifndef LED_HH
#define LED_HH

#include "component.hh"

struct LED : Component {

    COMPONENT_CONSTRUCTOR(LED)

    LED(ComponentType* ct, std::string const& serial) : LED(ct) {}

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
        COMPONENT_TYPE_INIT(LED, led)
        return &led;
    }

protected:
    std::string serialize_component() const override { return ""; }

private:
    bool value_ = false;
};



#endif //LED_HH
