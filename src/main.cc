#include "ui/ui.hh"

#include <chrono>

int main()
{
    std::unique_ptr<Graphics> graphics = std::make_unique<UI>();
    graphics->main_loop();

    UI ui;
    auto last_frame = hr::now();
    while (ui.running()) {
        auto new_frame = hr::now();
        ui.update(new_frame - last_frame);
        ui.render();
        last_frame = new_frame;
    }
}
