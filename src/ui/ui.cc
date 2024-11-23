#include "ui.hh"

#include <string>
using namespace std::string_literals;

#include "SDL2/SDL.h"
#include "SDL2/SDL_ttf.h"
#include "SDL2/SDL_image.h"

#include "spritesheet.hh"
#include "battery/embed.hpp"

UI::UI(Game& game)
    : game_(game)
{
    SDL_Init(SDL_INIT_EVERYTHING);
    TTF_Init();
    IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG);

    window_ = SDL_CreateWindow(PROJECT_NAME, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 1024, 800, SDL_WINDOW_RESIZABLE);
    if (!window_)
        throw std::runtime_error("Error: SDL_CreateWindow(): "s + SDL_GetError());

    ren_ = SDL_CreateRenderer(window_, -1, SDL_RENDERER_PRESENTVSYNC | SDL_RENDERER_ACCELERATED);
    if (!ren_)
        throw std::runtime_error("Error: SDL_CreateRenderer(): "s + SDL_GetError());

    SDL_RendererInfo info;
    SDL_GetRendererInfo(ren_, &info);
    SDL_Log("Current SDL_Renderer: %s", info.name);

    load_resources();
}

void UI::load_resources()
{
    std::vector<uint8_t> bg = b::embed<"resources/images/bg.jpg">().vec();
    SDL_Surface* sf = IMG_Load_RW(SDL_RWFromMem(bg.data(), (int) bg.size()), 1);
    bg_texture_ = SDL_CreateTextureFromSurface(ren_, sf);
    SDL_FreeSurface(sf);

    std::vector<uint8_t> circuit = b::embed<"resources/images/circuit.png">().vec();
    sf = IMG_Load_RW(SDL_RWFromMem(circuit.data(), (int) circuit.size()), 1);
    circuit_texture_ = SDL_CreateTextureFromSurface(ren_, sf);
    SDL_FreeSurface(sf);

    auto font_file = b::embed<"resources/fonts/04B_03__.TTF">();
    font_ = TTF_OpenFontRW(SDL_RWFromMem((void *) font_file.data(), (int) font_file.size()), 1, 16);

    cursors_[Cursor::Normal] = SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_ARROW);
    cursors_[Cursor::Delete] = SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_HAND);
}


UI::~UI()
{
    for (auto [i, cursor]: cursors_)
        if (cursor)
            SDL_FreeCursor(cursor);
    if (font_)            TTF_CloseFont(font_);
    if (bg_texture_)      SDL_DestroyTexture(bg_texture_);
    if (circuit_texture_) SDL_DestroyTexture(circuit_texture_);
    if (ren_)             SDL_DestroyRenderer(ren_);
    if (window_)          SDL_DestroyWindow(window_);
    IMG_Quit();
    TTF_Quit();
    SDL_Quit();
}

void UI::update(Duration timestep)
{
    SDL_Event e;
    while (SDL_PollEvent(&e)) {

        switch (e.type) {
            case SDL_QUIT:
                running_ = false;
                break;
            case SDL_MOUSEBUTTONDOWN: {
                auto toplevel = game_.topmost_toplevel_in_pos(e.button.x, e.button.y);
                if (toplevel) {
                    game_.bring_to_front(*toplevel);
                    if (e.button.button == SDL_BUTTON_RIGHT) {
                        moving_toplevel_ = *toplevel;
                        SDL_ShowCursor(SDL_DISABLE);
                    } else {
                        (*toplevel)->event_mouse_click(*this, e.button.x - (*toplevel)->position_x, e.button.y - (*toplevel)->position_y, (MouseButton) e.button.button);
                    }
                }
                break;
            }
            case SDL_MOUSEBUTTONUP:
                if (moving_toplevel_ && e.button.button == SDL_BUTTON_RIGHT) {
                    moving_toplevel_.reset();
                    SDL_ShowCursor(SDL_ENABLE);
                } else {
                    for (auto& tl: game_.toplevels())
                        tl->event_mouse_release(*this, e.button.x - tl->position_x, e.button.y - tl->position_y, (MouseButton) e.button.button);
                }
                break;
            case SDL_MOUSEMOTION: {
                auto toplevel = game_.topmost_toplevel_in_pos(e.motion.x, e.motion.y);
                if (toplevel)
                    (*toplevel)->event_mouse_move(*this, e.motion.x - (*toplevel)->position_x, e.motion.y - (*toplevel)->position_y, e.motion.xrel, e.motion.yrel);
                if (moving_toplevel_)
                    move_toplevel(*moving_toplevel_, e.motion.xrel, e.motion.yrel);
                break;
            }
            case SDL_KEYUP: {
                int mx, my;
                SDL_GetMouseState(&mx, &my);
                for (auto& tl: game_.toplevels())
                    tl->event_key_release(*this, e.key.keysym.sym, mx - tl->position_x, my - tl->position_y);
                break;
            }
            case SDL_KEYDOWN: {
                if (e.key.repeat == 0) {
                    int mx, my;
                    SDL_GetMouseState(&mx, &my);
                    auto toplevel = game_.topmost_toplevel_in_pos(mx, my);
                    if (toplevel) {
                        (*toplevel)->event_key_press(*this, e.key.keysym.sym, mx - (*toplevel)->position_x, my - (*toplevel)->position_y);
                    }
                }
                break;
            }
            default: break;
        }

        if (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_q)
            running_ = false;
    }
}

void UI::move_toplevel(TopLevel* toplevel, int xrel, int yrel)
{
    int scr_w, scr_h;
    SDL_GetWindowSize(window_, &scr_w, &scr_h);

    toplevel->position_x += xrel;
    toplevel->position_y += yrel;

    int space_left = 3.5 * TILE_SIZE * toplevel->zoom;
    toplevel->position_x = std::max(std::min(toplevel->position_x, (ssize_t) (scr_w - space_left)), (ssize_t) -toplevel->w() - space_left);
    toplevel->position_y = std::max(std::min(toplevel->position_y, (ssize_t) (scr_h - space_left)), (ssize_t) -toplevel->h() - space_left);
}

void UI::render()
{
    // clear screen
    SDL_RenderCopy(ren_, bg_texture_, nullptr, nullptr);

    render_game();

    SDL_RenderPresent(ren_);
}

void UI::render_game()
{
    for (auto const& toplevel : game_.toplevels()) {
        SDL_RenderSetScale(ren_, toplevel->zoom, toplevel->zoom);
        rel_x_ = toplevel->position_x / toplevel->zoom;
        rel_y_ = toplevel->position_y / toplevel->zoom;
        toplevel->draw(*this);
        rel_x_ = rel_y_ = 0;
        SDL_RenderSetScale(ren_, 1.f, 1.f);
    }
}

void UI::draw(Sprite sprite, ssize_t x, ssize_t y, DrawParameters const& p) const
{
    auto const& r = sprite_coordinates[(size_t) sprite];
    SDL_Rect src { .x = r.x * TILE_SIZE, .y = r.y * TILE_SIZE, .w = r.w * TILE_SIZE, .h = r.h * TILE_SIZE };
    SDL_Rect dest = { .x = (int) (rel_x_ + x), .y = (int) (rel_y_ + y), .w = src.w, .h = src.h };

    SDL_SetTextureAlphaMod(circuit_texture_, p.semitransparent ? 128 : 255);

    double angle = 0.0;
    if (p.direction == Direction::E)
        angle = 90.0;
    else if (p.direction == Direction::S)
        angle = 180.0;
    else if (p.direction == Direction::W)
        angle = -90.0;

    SDL_RenderCopyEx(ren_, circuit_texture_, &src, &dest, angle, nullptr, SDL_FLIP_NONE);
}

void UI::set_cursor(Cursor cursor)
{
    try {
        SDL_SetCursor(cursors_.at(cursor));
    } catch (std::out_of_range&) {}
}
