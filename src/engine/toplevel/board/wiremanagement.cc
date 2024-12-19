#include "wiremanagement.hh"

#include <vector>

void WireManagement::start_drawing(Position const& pos, WireWidth width, WireLayer side)
{
    drawing_wire_ = { .start_pos = pos, .end_pos = pos, .width = width, .side = side };
}

void WireManagement::set_current_end(Position const& end_pos)
{
    if (!drawing_wire_)
        return;

    drawing_wire_->end_pos = end_pos;

    if (drawing_wire_->start_pos == end_pos) {  // if user returns to starting place, we reset the orientation
        drawing_wire_->orientation.reset();
    }

    if (!drawing_wire_->orientation && drawing_wire_->start_pos != end_pos) {
        ssize_t dx = std::abs(drawing_wire_->start_pos.x - end_pos.x);
        ssize_t dy = std::abs(drawing_wire_->start_pos.y - end_pos.y);
        drawing_wire_->orientation = (dx >= dy) ? Orientation::Horizontal : Orientation::Vertical;
    }
}

WireMap WireManagement::stop_drawing(Position const& pos)
{
    set_current_end(pos);
    auto w = current_drawing();
    drawing_wire_.reset();
    return w;
}

WireMap WireManagement::current_drawing() const
{
    if (!drawing_wire_)
        return {};

    std::vector<SubPosition> vsp;

    auto add_straight_wire = [&vsp](Position const& from, Position const& to) {
        if (from.x == to.x && from.y < to.y) {   // vertical
            vsp.push_back({ .pos = from, .dir = Direction::S });
            for (ssize_t y = from.y + 1; y < to.y; ++y) {
                vsp.push_back({ .pos = { to.x, y }, .dir = Direction::N });
                vsp.push_back({ .pos = { to.x, y }, .dir = Direction::S });
            }
            vsp.push_back({ .pos = to, .dir = Direction::N });
        } else if (from.y == to.y && from.x < to.x) {  // horizontal
            vsp.push_back({ .pos = from, .dir = Direction::E });
            for (ssize_t x = from.x + 1; x < to.x; ++x) {
                vsp.push_back({ .pos = { x, from.y }, .dir = Direction::W });
                vsp.push_back({ .pos = { x, from.y }, .dir = Direction::E });
            }
            vsp.push_back({ .pos = to, .dir = Direction::W });
        } else {
            throw std::runtime_error("Invalid straight line.");
        }
    };

    // create wire path
    auto start = drawing_wire_->start_pos;
    auto end = drawing_wire_->end_pos;
    if (drawing_wire_->orientation == Orientation::Horizontal) {
        if (start.x != end.x)
            add_straight_wire({ std::min(start.x, end.x), start.y }, { std::max(start.x, end.x), start.y });
        if (start.y != end.y)
            add_straight_wire({ end.x, std::min(start.y, end.y) }, {  end.x, std::max(start.y, end.y) });
    } else if (drawing_wire_->orientation == Orientation::Vertical) {
        if (start.y != end.y)
            add_straight_wire({ start.x, std::min(start.y, end.y) }, {  start.x, std::max(start.y, end.y) });
        if (start.x != end.x)
            add_straight_wire({ std::min(start.x, end.x), end.y }, { std::max(start.x, end.x), end.y });
    }

    // create wire map out of wire path
    WireMap wm {};
    for (auto const& sp: vsp)
        wm[sp.pos].emplace(WireConfiguration {
            .width = drawing_wire_->width,
            .layer = drawing_wire_->side,
            .dir = sp.dir,
            .value = false,
        });
    return wm;
}
