#ifndef UI_UI_HH_
#define UI_UI_HH_

#include <chrono>
#include <unordered_map>

#include "graphics.hh"
#include "engine/sandbox.hh"

using hr = std::chrono::high_resolution_clock;
using Duration = decltype(hr::now() - hr::now());

class UI : public Graphics {
public:
    UI(Sandbox& sandbox);
    ~UI();
    UI (const UI&) = delete;
    UI& operator=(const UI&) = delete;

    void update([[maybe_unused]] Duration timestep);
    void render();

    [[nodiscard]] bool running() const { return running_; }

    void draw(Sprite sprite, ssize_t x, ssize_t y, DrawParameters const& p) const override;
    void set_cursor(Cursor cursor) override;

private:
    void load_resources();
    void render_sandbox();
    void move_toplevel(TopLevel* toplevel, int xrel, int yrel);

    Sandbox& sandbox_;

    bool running_ = true;
    bool show_demo_window_ = true;

    struct SDL_Window*   window_;
    struct SDL_Renderer* ren_;
    struct SDL_Texture*  bg_texture_ = nullptr;
    struct SDL_Texture*  circuit_texture_ = nullptr;
    struct _TTF_Font*    font_ = nullptr;

    ssize_t rel_x_ = 0, rel_y_ = 0;

    std::optional<TopLevel*> moving_toplevel_ {};
    std::unordered_map<Cursor, struct SDL_Cursor*> cursors_;
};

#endif
