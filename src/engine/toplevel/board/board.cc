#include "board.hh"

void Board::draw(Graphics& graphics) const
{
    graphics.draw_from_atlas(Sprite::BoardTopLeft, 0, 0);
}
