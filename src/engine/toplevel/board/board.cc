#include "board.hh"

void Board::draw(Graphics& graphics) const
{
    graphics.draw(Sprite::BoardTopLeft, 0, 0);
}
