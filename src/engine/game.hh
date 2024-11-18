#ifndef GAME_HH
#define GAME_HH

#include <memory>
#include <optional>
#include <vector>

#include "toplevel/toplevel.hh"
#include "toplevel/board/board.hh"

class Game {
public:
    Game() {
        toplevels_.push_back(std::make_unique<Board>());
    }

    [[nodiscard]] std::vector<std::unique_ptr<TopLevel>> const& toplevels() const { return toplevels_; }
    [[nodiscard]] std::optional<TopLevel*> topmost_toplevel_in_pos(ssize_t x, ssize_t y) const;

    void bring_to_front(TopLevel* toplevel);

private:
    std::vector<std::unique_ptr<TopLevel>> toplevels_;
};

#endif //GAME_HH
