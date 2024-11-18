#ifndef TOPLEVEL_HH
#define TOPLEVEL_HH

#include "ui/graphics.hh"

class TopLevel {
public:
    ssize_t x = 0, y = 0;           // position, in pixels
    float zoom = 2.f;

    virtual size_t w() const = 0;   // width, in pixels
    virtual size_t h() const = 0;   // height, in pixels

    virtual void draw(Graphics& graphics, ssize_t rel_x, ssize_t rel_y) const = 0;
};

#endif //TOPLEVEL_HH
