#include "ui/ui.hh"

#include <chrono>

#include "engine/game.hh"

int main()
{
    Game game;
    UI ui(game);

    auto last_frame = hr::now();
    while (ui.running()) {
        auto new_frame = hr::now();
        ui.update(new_frame - last_frame);
        ui.render();
        last_frame = new_frame;
    }
}
