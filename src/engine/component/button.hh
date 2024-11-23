#ifndef Button_HH
#define Button_HH

#include "component.hh"

struct Button : Component {

    COMPONENT_CONSTRUCTOR(Button)

    Button(ComponentType* ct, std::string const& serial) : Button(ct)
    {
        pressed_ = serial == "0";
    }

    std::vector<uint8_t> simulate([[maybe_unused]] std::vector<uint8_t> const& inputs) override
    {
        return { pressed_, pressed_, pressed_, pressed_ };
    }

    void on_click(size_t x, size_t y) override
    {
        pressed_ = !pressed_;
    }

    [[nodiscard]] ComponentImage component_image() const override
    {
        return std::vector<ComponentSprite> {
            { Sprite::ShadowSquare, 1, 1 },
            { pressed_ ? Sprite::ButtonOn : Sprite::ButtonOff }
        };
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
        COMPONENT_TYPE_INIT(Button, button)
        return &button;
    }

protected:
    std::string serialize_component() const override { return pressed_ ? "1" : "0"; }

private:
    bool pressed_ = false;
};


#endif //Button_HH
