#include "board.hh"

#include <stdexcept>

void Board::event_key_press(uint32_t key, ssize_t mouse_x, ssize_t mouse_y)
{
    if (key == 'w') {
        wire_management_.start_drawing(mouse_to_tile(mouse_x, mouse_y), WireWidth::W1, WireSide::Top);
    }
}

void Board::event_key_release(uint32_t key, ssize_t mouse_x, ssize_t mouse_y)
{
    if (key == 'w') {
        wires_ = wire_management_.stop_drawing(mouse_to_tile(mouse_x, mouse_y));
    }
}

void Board::event_mouse_move(ssize_t x, ssize_t y, ssize_t xrel, ssize_t yrel)
{
    wire_management_.set_current_end(mouse_to_tile(x, y));
}

void Board::draw(Graphics& graphics) const
{
    draw_board_borders(graphics);
    for (ssize_t x = 0; x < board_w_; ++x)
        for (ssize_t y = 0; y < board_h_; ++y)
            draw_tile(graphics, { x, y });
}

void Board::draw_board_borders(Graphics& graphics) const
{
    graphics.draw(Sprite::BoardTopLeft, 0, 0);
    graphics.draw(Sprite::BoardTopRight, (board_w_ + 2) * TILE_SIZE, 0);
    graphics.draw(Sprite::BoardBottomLeft, 0, (board_h_ + 2) * TILE_SIZE);
    graphics.draw(Sprite::BoardBottomRight, (board_w_ + 2) * TILE_SIZE, (board_h_ + 2) * TILE_SIZE);

    for (ssize_t x = 0; x < board_w_; ++x) {
        graphics.draw(Sprite::BoardTop, (x + 2) * TILE_SIZE, 0);
        graphics.draw(Sprite::BoardBottom, (x + 2) * TILE_SIZE, (board_h_ + 2) * TILE_SIZE);
    }

    for (ssize_t y = 0; y < board_h_; ++y) {
        graphics.draw(Sprite::BoardLeft, 0 * TILE_SIZE, (y + 2) * TILE_SIZE);
        graphics.draw(Sprite::BoardRight, (board_w_ + 2) * TILE_SIZE, (y + 2) * TILE_SIZE);
    }
}

void Board::draw_tile(Graphics& graphics, Position const& pos) const
{
    graphics.draw(Sprite::Tile, (pos.x + 2) * TILE_SIZE, (pos.y + 2) * TILE_SIZE);

    // draw wire
    {
        auto it = wires_.find(pos);
        if (it != wires_.end())
            draw_wires(graphics, pos, it->second, false);
    }

    // draw temporary wire
    {
        auto const& cd = wire_management_.current_drawing();
        auto it = cd.find(pos);
        if (it != cd.end())
            draw_wires(graphics, pos, it->second, true);
    }
}

void Board::draw_wires(Graphics& graphics, Position const& pos, WireSet const& wcs, bool semitransparent) const
{
    static const std::unordered_map<WireConfiguration, Sprite> wire_sprites {
        { { WireWidth::W1, WireSide::Top, Direction::N, true }, Sprite::WireTopOnNorth_1 },
        { { WireWidth::W1, WireSide::Top, Direction::S, true }, Sprite::WireTopOnSouth_1 },
        { { WireWidth::W1, WireSide::Top, Direction::W, true }, Sprite::WireTopOnWest_1 },
        { { WireWidth::W1, WireSide::Top, Direction::E, true }, Sprite::WireTopOnEast_1 },
        { { WireWidth::W1, WireSide::Top, Direction::N, false }, Sprite::WireTopOffNorth_1 },
        { { WireWidth::W1, WireSide::Top, Direction::S, false }, Sprite::WireTopOffSouth_1 },
        { { WireWidth::W1, WireSide::Top, Direction::W, false }, Sprite::WireTopOffWest_1 },
        { { WireWidth::W1, WireSide::Top, Direction::E, false }, Sprite::WireTopOffEast_1 },
    };

    for (WireConfiguration const& wc: wcs) {
        auto it = wire_sprites.find(wc);
        if (it != wire_sprites.end())
            throw std::runtime_error("Wire configuration not found");
        graphics.draw(it->second, (pos.x + 2) * TILE_SIZE, (pos.y + 2) * TILE_SIZE, semitransparent);
    }
}

Position Board::mouse_to_tile(ssize_t mx, ssize_t my)
{
    return {
        .x = mx / TILE_SIZE - 2,
        .y = my / TILE_SIZE - 2,
    };
}
