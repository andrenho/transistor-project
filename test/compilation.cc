#include "doctest.h"

#include "engine/sandbox.hh"
#include "engine/component/button.hh"
#include "engine/component/led.hh"
#include "engine/simulation/compiler.cc"

#include <algorithm>
#include <ranges>
namespace r = std::ranges;

TEST_SUITE("Compilation")
{
    TEST_CASE("Simple circuit") {
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

        SUBCASE("Find connections") {
            const auto pins = compiler::find_all_pins(sandbox);
            const compiler::Pin starting_pin = { .component = button, .pin_no = 1, .spos = { { 1, 1 }, Direction::E } };

            compiler::Connection connection = find_connections(starting_pin, pins);

            compiler::Pin expected_pin_1 { .component = button, .pin_no = 1, .spos = { { 1, 1 }, Direction::E } };
            compiler::Pin expected_pin_2 { .component = led, .pin_no = 0, .spos = { { 3, 2 }, Direction::N } };
            CHECK(connection.pins.size() == 2);
            CHECK(r::find_if(connection.pins, [&](auto const& pin) { return pin == expected_pin_1; }) != connection.pins.end());
            CHECK(r::find_if(connection.pins, [&](auto const& pin) { return pin == expected_pin_2; }) != connection.pins.end());

            CHECK(connection.wires.size() == 6);
            CHECK(r::find_if(connection.wires, [](auto const& spos) { return spos == SubPosition { { 1, 1 }, Direction::E }; }) != connection.wires.end());
            CHECK(r::find_if(connection.wires, [](auto const& spos) { return spos == SubPosition { { 2, 1 }, Direction::W }; }) != connection.wires.end());
            CHECK(r::find_if(connection.wires, [](auto const& spos) { return spos == SubPosition { { 2, 1 }, Direction::E }; }) != connection.wires.end());
            CHECK(r::find_if(connection.wires, [](auto const& spos) { return spos == SubPosition { { 3, 1 }, Direction::W }; }) != connection.wires.end());
            CHECK(r::find_if(connection.wires, [](auto const& spos) { return spos == SubPosition { { 3, 1 }, Direction::S }; }) != connection.wires.end());
            CHECK(r::find_if(connection.wires, [](auto const& spos) { return spos == SubPosition { { 3, 2 }, Direction::N }; }) != connection.wires.end());
        }
    }
}