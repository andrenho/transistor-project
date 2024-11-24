#ifndef BOARD_HH
#define BOARD_HH

#include "wireconfiguration.hh"
#include "wiremanagement.hh"
#include "../toplevel.hh"
#include "engine/position.hh"
#include "engine/component/component.hh"

class Board : public TopLevel {
public:
    explicit Board(Sandbox& sandbox) : TopLevel(sandbox) {}

    size_t w() const override { return (board_w_ + 4) * TILE_SIZE; }
    size_t h() const override { return (board_h_ + 4) * TILE_SIZE; }

    void draw(Graphics& graphics) const override;

    void add_component(Position const& pos, ComponentType const* component_type);
    void add_wire(Position const& start, Position const& end, Orientation orientation, WireWidth width, WireSide side);

    void event_key_press(Graphics& graphics, uint32_t key, ssize_t mouse_x, ssize_t mouse_y) override;
    void event_key_release(Graphics& graphics, uint32_t key, ssize_t mouse_x, ssize_t mouse_y) override;
    void event_mouse_move(Graphics& graphics, ssize_t x, ssize_t y, ssize_t xrel, ssize_t yrel) override;
    void event_mouse_click(Graphics& graphics, ssize_t x, ssize_t y, MouseButton button) override;

    [[nodiscard]] WireMap const&      wires() const override { return wires_; }
    [[nodiscard]] ComponentMap const& components() const override { return components_; }

private:
    ssize_t board_w_ = 10;
    ssize_t board_h_ = 10;

    void merge_wires(WireMap const& wm);

    void clear_tile(Position const& pos);
    void rotate_tile(Position const& pos);

    void draw_board_borders(Graphics& graphics) const;
    void draw_tile(Graphics& graphics, Position const& pos) const;
    void draw_wires(Graphics& graphics, Position const& pos, WireSet const& wcs, bool semitransparent) const;

    Position mouse_to_tile(ssize_t mx, ssize_t my) const;

    WireManagement wire_management_;
    WireMap        wires_ {};
    ComponentMap   components_ {};
    bool           clearing_tiles_ = false;
};

#endif //BOARD_HH
