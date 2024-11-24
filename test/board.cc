#include "doctest.h"

#include "engine/sandbox.hh"
#include "engine/component/button.hh"
#include "engine/component/led.hh"

#include <ranges>
namespace r = std::ranges;

TEST_CASE("Adding components") {

    Sandbox sandbox;
    REQUIRE(sandbox.toplevels().size() == 1);

    Board* board = dynamic_cast<Board*>(sandbox.toplevels().at(0).get());
    board->add_component({ 1, 1 }, Button::component_type());

    auto const& components = board->components();
    CHECK(components.size() == 1);

    Button* button = dynamic_cast<Button*>(components.at({ 1, 1 }).get());
    CHECK(button);
    CHECK(button->component_type() == Button::component_type());
}

TEST_CASE("Adding wires") {

    Sandbox sandbox;
    Board* board = dynamic_cast<Board*>(sandbox.toplevels().at(0).get());
    board->add_wire({ 1, 1 }, { 3, 2 }, Orientation::Horizontal, WireWidth::W1, WireSide::Top);

    /***1***2***3**
     1* --+---+-. *
      **********|**
     2*   *   * | *
      *************/

    auto const& wires = board->wires();
    CHECK(wires.size() == 4);

    auto has_wire = [&wires](SubPosition const& spos) {
        auto const& it = wires.find(spos.pos);
        if (it != wires.end()) {
            auto it2 = r::find_if(it->second, [&spos](WireConfiguration const& wc) { return wc.dir == spos.dir; });
            if (it2 != it->second.end())
                return true;
        }
        return false;
    };

    CHECK(has_wire({ { 1, 1 }, Direction::E }));
    CHECK(has_wire({ { 2, 1 }, Direction::W }));
    CHECK(has_wire({ { 2, 1 }, Direction::E }));
    CHECK(has_wire({ { 3, 1 }, Direction::W }));
    CHECK(has_wire({ { 3, 1 }, Direction::S }));
    CHECK(has_wire({ { 3, 2 }, Direction::N }));
}