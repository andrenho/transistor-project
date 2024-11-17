#ifndef GAME_HH
#define GAME_HH

#include <memory>
#include <vector>

#include "toplevel/board.hh"
#include "toplevel/toplevel.hh"

class Game {
public:
    [[nodiscard]] std::vector<std::unique_ptr<TopLevel>> const& toplevels() const { return toplevels_; }

private:
    std::vector<std::unique_ptr<TopLevel>> toplevels_ = {
        std::make_unique<Board>()
    };
};

#endif //GAME_HH
