#include "graphics.hh"

void Graphics::main_loop()
{
    auto last_frame = hr::now();
    while (running_) {
        auto new_frame = hr::now();
        update(new_frame - last_frame);
        render();
        last_frame = new_frame;
    }
}
