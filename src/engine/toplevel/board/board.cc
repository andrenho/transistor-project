#include "board.hh"

#include <stdexcept>

#include "engine/game.hh"
#include "util/visitor.hh"

//
// EVENTS
//

void Board::event_key_press(Graphics& graphics, uint32_t key, ssize_t mouse_x, ssize_t mouse_y)
{
    auto tpos = mouse_to_tile(mouse_x, mouse_y);
    switch (key) {
        case 'w':
            wire_management_.start_drawing(tpos, WireWidth::W1, WireSide::Top);
            break;
        case 'x':
            clearing_tiles_ = true;
            graphics.set_cursor(Cursor::Delete);
            clear_tile(tpos);
            break;
        case 'r':
            rotate_tile(tpos);
            break;
        default:
            for (auto const* ct: game_.component_types()) {
                if (key == ct->key_to_place)
                    add_component(tpos, ct);
            }
    }
}

void Board::event_key_release(Graphics& graphics, uint32_t key, ssize_t mouse_x, ssize_t mouse_y)
{
    auto tpos = mouse_to_tile(mouse_x, mouse_y);
    if (key == 'w') {
        merge_wires(wire_management_.stop_drawing(tpos));
    } else if (key == 'x') {
        clearing_tiles_ = false;
        graphics.set_cursor(Cursor::Normal);
    }
}

void Board::event_mouse_move(Graphics& graphics, ssize_t x, ssize_t y, ssize_t xrel, ssize_t yrel)
{
    auto tpos = mouse_to_tile(x, y);

    wire_management_.set_current_end(tpos);

    if (clearing_tiles_)
        clear_tile(tpos);
}

void Board::event_mouse_click(Graphics& graphics, ssize_t x, ssize_t y, MouseButton button)
{
    Position tile = mouse_to_tile(x, y);
    if (auto it = components_.find(tile); it != components_.end()) {
        it->second->on_click(0, 0);  // TODO
    }
}

//
// MODIFY BOARD
//

void Board::add_component(Position const& pos, ComponentType const* component_type)
{
    if (!component_type->create_component)
        throw std::runtime_error("Component cannot be initialized (missing `create_component`)");
    components_[pos] = component_type->create_component();
}

void Board::merge_wires(WireMap const& wm)
{
    for (auto const& [pos, ws]: wm) {
        wires_[pos].insert(ws.begin(), ws.end());
    }
}

void Board::clear_tile(Position const& pos)
{
    wires_.erase(pos);
    components_.erase(pos);
}

void Board::rotate_tile(Position const& pos)
{
    if (auto it = components_.find(pos); it != components_.end())
        it->second->rotate();
}

//
// DRAWING
//

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
        if (auto const it = wires_.find(pos); it != wires_.end())
            draw_wires(graphics, pos, it->second, false);
    }

    // draw temporary wire
    {
        auto const& cd = wire_management_.current_drawing();
        if (auto const it = cd.find(pos); it != cd.end())
            draw_wires(graphics, pos, it->second, true);
    }

    // component
    {
        if (auto const it = components_.find(pos); it != components_.end())
            std::visit(overloaded {
                [&](std::vector<Sprite> const& vsp) {
                    for (const Sprite sp: vsp)
                        graphics.draw(sp, (pos.x + 2) * TILE_SIZE, (pos.y + 2) * TILE_SIZE);
                },
            }, it->second->component_image());
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
        if (it == wire_sprites.end())
            throw std::runtime_error("Wire configuration not found");
        graphics.draw(it->second, (pos.x + 2) * TILE_SIZE, (pos.y + 2) * TILE_SIZE, { .semitransparent = semitransparent });
    }
}

Position Board::mouse_to_tile(ssize_t mx, ssize_t my) const
{
    return {
        .x = (ssize_t) (mx / TILE_SIZE / zoom - 2),
        .y = (ssize_t) (my / TILE_SIZE / zoom - 2),
    };
}
