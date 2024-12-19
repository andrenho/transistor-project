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
    TEST_CASE("Simple circuit")
    {
        Sandbox sandbox;
        auto board = dynamic_cast<Board*>(sandbox.toplevels().at(0).get());
        Component* button = board->add_component({ 1, 1 }, Button::component_type());
        Component* led = board->add_component({ 3, 2 }, LED::component_type());
        board->add_wire({ 1, 1 }, { 3, 2 }, Orientation::Horizontal, WireWidth::W1, WireLayer::Top);

        SUBCASE("find all pins")
        {
            const auto pins = compiler::find_all_pins(*board);

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

        SUBCASE("find wire positions")
        {
            const auto wire_pos = compiler::find_full_wire(*board, { .pos = {1, 1}, .dir = Direction::E }, WireLayer::Top);

            CHECK(wire_pos.contains({ .pos = { 1, 1 }, .dir = Direction::E }));
            CHECK(wire_pos.contains({ .pos = { 2, 1 }, .dir = Direction::W }));
            CHECK(wire_pos.contains({ .pos = { 2, 1 }, .dir = Direction::E }));
            CHECK(wire_pos.contains({ .pos = { 3, 1 }, .dir = Direction::W }));
            CHECK(wire_pos.contains({ .pos = { 3, 1 }, .dir = Direction::S }));
            CHECK(wire_pos.contains({ .pos = { 3, 2 }, .dir = Direction::N }));

            CHECK(wire_pos.size() == 6);
        }

        /*
        SUBCASE("Find connections")
        {
            const auto pins = compiler::find_all_pins(sandbox);
            const compiler::Pin starting_pin = { .component = button, .pin_no = 1, .spos = { { 1, 1 }, Direction::E } };

            compiler::Connection connection = find_connections(sandbox, starting_pin, pins, WireLayer::Top);

            compiler::Pin expected_pin_1 { .component = button, .pin_no = 1, .spos = { { 1, 1 }, Direction::E } };
            compiler::Pin expected_pin_2 { .component = led, .pin_no = 0, .spos = { { 3, 2 }, Direction::N } };

            CHECK(connection.wire_width == WireWidth::W1);
            CHECK(connection.wire_layer == WireLayer::Top);

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
        */
    }

    TEST_CASE("Split wire")
    {
        Sandbox sandbox;
        auto board = dynamic_cast<Board*>(sandbox.toplevels().at(0).get());
        board->add_wire({ 1, 1 }, { 3, 2 }, Orientation::Horizontal, WireWidth::W1, WireLayer::Top);
        board->add_wire({ 2, 1 }, { 2, 3 }, Orientation::Vertical, WireWidth::W1, WireLayer::Top);
        board->add_wire({ 4, 0 }, { 4, 2 }, Orientation::Vertical, WireWidth::W1, WireLayer::Top);

        SUBCASE("split wire")
        {
            const auto wire_pos = compiler::find_full_wire(*board, { .pos = {1, 1}, .dir = Direction::E }, WireLayer::Top);

            // 1st wire
            CHECK(wire_pos.contains({ .pos = { 1, 1 }, .dir = Direction::E }));
            CHECK(wire_pos.contains({ .pos = { 2, 1 }, .dir = Direction::W }));
            CHECK(wire_pos.contains({ .pos = { 2, 1 }, .dir = Direction::E }));
            CHECK(wire_pos.contains({ .pos = { 3, 1 }, .dir = Direction::W }));
            CHECK(wire_pos.contains({ .pos = { 3, 1 }, .dir = Direction::S }));
            CHECK(wire_pos.contains({ .pos = { 3, 2 }, .dir = Direction::N }));

            // 2nd wire
            CHECK(wire_pos.contains({ .pos = { 2, 1 }, .dir = Direction::S }));
            CHECK(wire_pos.contains({ .pos = { 2, 2 }, .dir = Direction::N }));
            CHECK(wire_pos.contains({ .pos = { 2, 2 }, .dir = Direction::S }));
            CHECK(wire_pos.contains({ .pos = { 2, 3 }, .dir = Direction::N }));

            CHECK(wire_pos.size() == 10);
        }

        SUBCASE("2nd wire")
        {
            const auto wire_pos = compiler::find_full_wire(*board, { .pos = {4, 0}, .dir = Direction::S }, WireLayer::Top);

            CHECK(wire_pos.contains({ .pos = { 4, 0 }, .dir = Direction::S }));
            CHECK(wire_pos.contains({ .pos = { 4, 1 }, .dir = Direction::N }));
            CHECK(wire_pos.contains({ .pos = { 4, 1 }, .dir = Direction::S }));
            CHECK(wire_pos.contains({ .pos = { 4, 2 }, .dir = Direction::N }));

            CHECK(wire_pos.size() == 4);
        }
    }

    TEST_CASE("wire crossing (connected)")
    {
        Sandbox sandbox;
        auto board = dynamic_cast<Board*>(sandbox.toplevels().at(0).get());
        board->add_wire({ 1, 1 }, { 3, 1 }, Orientation::Horizontal, WireWidth::W1, WireLayer::Top);
        board->add_wire({ 0, 2 }, { 2, 2 }, Orientation::Vertical, WireWidth::W1, WireLayer::Top);

        SUBCASE("crossing wire")
        {
            const auto wire_pos = compiler::find_full_wire(*board, { .pos = {1, 1}, .dir = Direction::S }, WireLayer::Top);

            CHECK(wire_pos.contains({ .pos = { 2, 1 }, .dir = Direction::N }));
            CHECK(wire_pos.contains({ .pos = { 2, 1 }, .dir = Direction::S }));
            CHECK(wire_pos.contains({ .pos = { 2, 1 }, .dir = Direction::W }));
            CHECK(wire_pos.contains({ .pos = { 2, 1 }, .dir = Direction::E }));

            CHECK(wire_pos.size() == 8);
        }
    }
}