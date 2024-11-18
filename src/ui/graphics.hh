#ifndef GRAPHICS_HH
#define GRAPHICS_HH

#include <chrono>

#include "spritesheet.hh"

class Graphics {
public:
    virtual ~Graphics() = default;

    virtual void draw_from_atlas(Sprite sprite, ssize_t x, ssize_t, bool semitransparent=false) const = 0;
};

#endif //GRAPHICS_HH
