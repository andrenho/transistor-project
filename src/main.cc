#include "ui/ui.hh"

#include <chrono>

#include "engine/game.hh"

int main()
{
    Game game;
    UI(game).main_loop();
}
