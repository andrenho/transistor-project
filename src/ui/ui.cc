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
}


UI::~UI()
{
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
            default: break;
        }

        if (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_q)
            running_ = false;
    }
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
        rel_x_ = toplevel->x;
        rel_y_ = toplevel->y;
        toplevel->draw(*this);
        rel_x_ = rel_y_ = 0;
        SDL_RenderSetScale(ren_, 1.f, 1.f);
    }
}

void UI::draw_from_atlas(Sprite sprite, ssize_t x, ssize_t y, bool semitransparent) const
{
    auto const& r = sprite_coordinates[(size_t) sprite];
    SDL_Rect src { .x = r.x * TILE_SIZE, .y = r.y * TILE_SIZE, .w = r.w * TILE_SIZE, .h = r.h * TILE_SIZE };
    SDL_Rect dest = { .x = (int) (rel_x_ + (x * TILE_SIZE)), .y = (int) (rel_y_ + (y * TILE_SIZE)), .w = src.w, .h = src.h };
    SDL_SetTextureAlphaMod(circuit_texture_, semitransparent ? 128 : 255);
    SDL_RenderCopy(ren_, circuit_texture_, &src, &dest);
}
