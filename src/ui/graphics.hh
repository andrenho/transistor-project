#ifndef GRAPHICS_HH
#define GRAPHICS_HH

#include <chrono>

#include "engine/game.hh"

using hr = std::chrono::high_resolution_clock;
using Duration = decltype(hr::now() - hr::now());

class Graphics {
public:
    virtual ~Graphics() = default;

    void main_loop();

protected:
    Graphics(Game& game) : game_(game) {}

    virtual void update([[maybe_unused]] Duration timestep) = 0;
    virtual void render() = 0;

private:
    Game& game_;
    bool running_ = true;
};

#endif //GRAPHICS_HH
