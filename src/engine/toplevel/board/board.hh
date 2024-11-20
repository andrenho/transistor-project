#ifndef BOARD_HH
#define BOARD_HH

#include "wireconfiguration.hh"
#include "wiremanagement.hh"
#include "../toplevel.hh"
#include "engine/position.hh"
#include "engine/component/component.hh"

using ComponentMap = std::unordered_map<Position, std::unique_ptr<Component>>;

class Board : public TopLevel {
public:
    size_t w() const override { return (board_w_ + 4) * TILE_SIZE; }
    size_t h() const override { return (board_h_ + 4) * TILE_SIZE; }

    void draw(Graphics& graphics) const override;

    void event_key_press(uint32_t key, ssize_t mouse_x, ssize_t mouse_y) override;
    void event_key_release(uint32_t key, ssize_t mouse_x, ssize_t mouse_y) override;
    void event_mouse_move(ssize_t x, ssize_t y, ssize_t xrel, ssize_t yrel) override;

    [[nodiscard]] WireMap const& wires() const { return wires_; }

private:
    ssize_t board_w_ = 10;
    ssize_t board_h_ = 10;

    void merge_wires(WireMap const& wm);

    void draw_board_borders(Graphics& graphics) const;
    void draw_tile(Graphics& graphics, Position const& pos) const;
    void draw_wires(Graphics& graphics, Position const& pos, WireSet const& wcs, bool semitransparent) const;

    Position mouse_to_tile(ssize_t mx, ssize_t my) const;

    WireManagement wire_management_;
    WireMap        wires_ {};
    ComponentMap   components_ {};
};

#endif //BOARD_HH
