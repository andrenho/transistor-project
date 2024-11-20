#ifndef GAME_HH
#define GAME_HH

#include <memory>
#include <optional>
#include <vector>

#include "component/component.hh"
#include "component/components.hh"
#include "toplevel/toplevel.hh"
#include "toplevel/board/board.hh"

class Game {
public:
    Game() {
        toplevels_.emplace_back(std::make_unique<Board>());
    }

    [[nodiscard]] std::vector<std::unique_ptr<TopLevel>> const& toplevels() const { return toplevels_; }
    [[nodiscard]] std::optional<TopLevel*> topmost_toplevel_in_pos(ssize_t x, ssize_t y) const;

    void bring_to_front(TopLevel* toplevel);

private:
    std::vector<std::unique_ptr<TopLevel>> toplevels_;
    std::vector<ComponentType> component_types_ = default_component_types();
};

#endif //GAME_HH
