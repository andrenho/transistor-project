#ifndef GRAPHICS_HH
#define GRAPHICS_HH

#include <chrono>

#include "spritesheet.hh"
#include "engine/position.hh"

enum class MouseButton { Left=1, Middle=2, Right=3 };
enum class Cursor { Normal, Delete };

struct DrawParameters {
    bool      semitransparent = false;
    Direction direction = Direction::N;
};

class Graphics {
public:
    virtual ~Graphics() = default;

    virtual void draw(Sprite sprite, ssize_t x, ssize_t, DrawParameters const& p = {}) const = 0;
    virtual void set_cursor(Cursor cursor) = 0;
};

#endif //GRAPHICS_HH
