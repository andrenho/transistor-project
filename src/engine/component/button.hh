#ifndef Button_HH
#define Button_HH

#include "component.hh"

struct Button : Component {

    COMPONENT_CONSTRUCTOR(Button)

    Button(ComponentType* ct, std::string const& serial) : Button(ct)
    {
        value_ = serial == "0";
    }

    std::vector<uint8_t> simulate([[maybe_unused]] std::vector<uint8_t> const& inputs) override
    {
        return { value_, value_, value_, value_ };
    }

    void on_click(size_t x, size_t y) override
    {
        value_ = !value_;
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
        COMPONENT_TYPE_INIT(Button, button)
        return &button;
    }

protected:
    std::string serialize_component() const override { return value_ ? "1" : "0"; }

private:
    bool value_ = false;
};


#endif //Button_HH
