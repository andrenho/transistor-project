#ifndef GAME_HH
#define GAME_HH

#include <memory>
#include <vector>

#include "toplevel/toplevel.hh"
#include "toplevel/board/board.hh"

class Game {
public:
    Game() {
        toplevels_.push_back(std::make_unique<Board>());
    }

    [[nodiscard]] std::vector<std::unique_ptr<TopLevel>> const& toplevels() const { return toplevels_; }

private:
    std::vector<std::unique_ptr<TopLevel>> toplevels_;
};

#endif //GAME_HH
