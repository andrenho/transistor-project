#ifndef GRAPHICS_HH
#define GRAPHICS_HH

#include <chrono>

#include "spritesheet.hh"

enum class MouseButton { Left=1, Middle=2, Right=3 };

class Graphics {
public:
    virtual ~Graphics() = default;

    virtual void draw(Sprite sprite, ssize_t x, ssize_t, bool semitransparent=false) const = 0;
};

#endif //GRAPHICS_HH
