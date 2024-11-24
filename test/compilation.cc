#include "doctest.h"

#include "engine/sandbox.hh"
#include "engine/component/button.hh"
#include "engine/component/led.hh"
#include "engine/simulation/compiler.cc"

TEST_CASE("Compilation - simple circuit") {
    Sandbox sandbox;
    Board* board = dynamic_cast<Board*>(sandbox.toplevels().at(0).get());
    Component* button = board->add_component({ 1, 1 }, Button::component_type());
    Component* led = board->add_component({ 3, 2 }, LED::component_type());
    board->add_wire({ 1, 1 }, { 3, 2 }, Orientation::Horizontal, WireWidth::W1, WireSide::Top);

    SUBCASE("find all pins") {
        const auto pins = compiler::find_all_pins(sandbox);

        CHECK(pins.size() == 8);

        CHECK(pins.contains({ .component = button, .pin_no = 0, .spos = { { 1, 1 }, Direction::N } }));
        CHECK(pins.contains({ .component = button, .pin_no = 1, .spos = { { 1, 1 }, Direction::E } }));
        CHECK(pins.contains({ .component = button, .pin_no = 2, .spos = { { 1, 1 }, Direction::S } }));
        CHECK(pins.contains({ .component = button, .pin_no = 3, .spos = { { 1, 1 }, Direction::W } }));

        CHECK(pins.contains({ .component = led, .pin_no = 0, .spos = { { 3, 2 }, Direction::N } }));
        CHECK(pins.contains({ .component = led, .pin_no = 1, .spos = { { 3, 2 }, Direction::E } }));
        CHECK(pins.contains({ .component = led, .pin_no = 2, .spos = { { 3, 2 }, Direction::S } }));
        CHECK(pins.contains({ .component = led, .pin_no = 3, .spos = { { 3, 2 }, Direction::W } }));
    }

    SUBCASE("find connections") {
        const auto pins = compiler::find_all_pins(sandbox);
        const compiler::Pin starting_pin = { .component = button, .pin_no = 1, .spos = { { 1, 1 }, Direction::E } };

        compiler::Connection connections = find_connections(starting_pin, pins);

        // TODO
    }
}