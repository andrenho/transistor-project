#include "doctest.h"

#include "engine/sandbox.hh"
#include "engine/component/button.hh"
#include "engine/component/led.hh"
#include "engine/simulation/compiler.cc"

TEST_CASE("Compilation") {
    Sandbox sandbox;
    Board* board = dynamic_cast<Board*>(sandbox.toplevels().at(0).get());
    Component* button = board->add_component({ 1, 1 }, Button::component_type());
    Component* led = board->add_component({ 3, 2 }, LED::component_type());
    board->add_wire({ 1, 1 }, { 3, 2 }, Orientation::Horizontal, WireWidth::W1, WireSide::Top);

    SUBCASE("find all pins") {
        auto pins = compiler::find_all_pins(sandbox);
        CHECK(pins.contains({
            .pin_no = 0,
            .component = button,
            .spos = { { 1, 1 }, Direction::N }
        }));
    }
}