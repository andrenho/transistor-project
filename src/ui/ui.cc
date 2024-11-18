#include "ui.hh"

#include <string>
using namespace std::string_literals;

#include "SDL2/SDL.h"
#include "SDL2/SDL_ttf.h"
#include "SDL2/SDL_image.h"

#include "battery/embed.hpp"

UI::UI(Game& game)
    : game_(game)
{
    SDL_Init(SDL_INIT_EVERYTHING);
    TTF_Init();
    IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG);

    window_ = SDL_CreateWindow(PROJECT_NAME, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 800, 600, SDL_WINDOW_RESIZABLE);
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

    auto font_file = b::embed<"resources/fonts/04B_03__.TTF">();
    font_ = TTF_OpenFontRW(SDL_RWFromMem((void *) font_file.data(), (int) font_file.size()), 1, 16);
}


UI::~UI()
{
    if (bg_texture_)
        SDL_DestroyTexture(bg_texture_);
    if (ren_)
        SDL_DestroyRenderer(ren_);
    if (window_)
        SDL_DestroyWindow(window_);
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
}
