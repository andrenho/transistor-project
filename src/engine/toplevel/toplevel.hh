#ifndef TOPLEVEL_HH
#define TOPLEVEL_HH

#include "ui/graphics.hh"

class TopLevel {
public:
    ssize_t position_x = 0, position_y = 0;           // position, in pixels
    float zoom = 2.f;

    virtual size_t w() const = 0;   // width, in pixels
    virtual size_t h() const = 0;   // height, in pixels

    virtual void draw(Graphics& graphics) const = 0;

    virtual void event_mouse_click(ssize_t x, ssize_t y, MouseButton button) {}
    virtual void event_mouse_release(ssize_t x, ssize_t y, MouseButton button) {}
    virtual void event_mouse_move(ssize_t x, ssize_t y, ssize_t xrel, ssize_t yrel) {}
    virtual void event_key_press(uint32_t key, ssize_t mouse_x, ssize_t mouse_y) {}
    virtual void event_key_release(uint32_t key, ssize_t mouse_x, ssize_t mouse_y) {}

    virtual ~TopLevel() = default;
};

#endif //TOPLEVEL_HH
