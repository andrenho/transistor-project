#ifndef BOARD_HH
#define BOARD_HH

#include "../toplevel.hh"

class Board : public TopLevel {
public:
    size_t w() const override { return (board_w_ + 4) * TILE_SIZE; }
    size_t h() const override { return (board_h_ + 4) * TILE_SIZE; }

    void draw(Graphics& graphics) const override;

private:
    ssize_t board_w_ = 10;
    ssize_t board_h_ = 10;

    void draw_board_borders(Graphics& graphics) const;
    void draw_tile(Graphics& graphics, size_t x, size_t y) const;
};

#endif //BOARD_HH
