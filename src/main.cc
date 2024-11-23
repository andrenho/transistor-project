#include "ui/ui.hh"

#include <chrono>

#include "engine/sandbox.hh"

int main()
{
    Sandbox sandbox;
    UI ui(sandbox);

    auto last_frame = hr::now();
    while (ui.running()) {
        auto new_frame = hr::now();
        ui.update(new_frame - last_frame);
        ui.render();
        last_frame = new_frame;
    }
}
