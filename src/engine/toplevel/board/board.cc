#include "board.hh"

void Board::keypress(uint32_t key, ssize_t mouse_x, ssize_t mouse_y)
{
    printf("%c\n", key);
}

void Board::draw(Graphics& graphics) const
{
    draw_board_borders(graphics);
    for (size_t x = 0; x < board_w_; ++x)
        for (size_t y = 0; y < board_h_; ++y)
            draw_tile(graphics, x, y);
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

void Board::draw_tile(Graphics& graphics, size_t x, size_t y) const
{
    graphics.draw(Sprite::Tile, (x + 2) * TILE_SIZE, (y + 2) * TILE_SIZE);
}
