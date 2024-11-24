#include "doctest.h"

#include "engine/sandbox.hh"
#include "engine/component/button.hh"
#include "engine/component/led.hh"

/*
TEST_CASE("Basic circuit compilation") {
    Sandbox sandbox;
    Board* board = dynamic_cast<Board*>(sandbox.toplevels().at(0).get());
    board->add_component({ 1, 1 }, Button::component_type());
    board->add_component({ 3, 1 }, LED::component_type());
}
*/