#ifndef BOARD_HH
#define BOARD_HH

#include "../toplevel.hh"

class Board : public TopLevel {
    static constexpr ssize_t TILE_SIZE = 16;

public:
    size_t w() const override { return (board_w_ + 4) * TILE_SIZE; }
    size_t h() const override { return (board_h_ + 4) * TILE_SIZE; }

    void draw(Graphics& graphics, ssize_t rel_x, ssize_t rel_y) const override;

private:
    ssize_t board_w_ = 10;
    ssize_t board_h_ = 10;
};

#endif //BOARD_HH
