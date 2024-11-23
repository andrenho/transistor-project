#ifndef SANDBOX_HH
#define SANDBOX_HH

#include <memory>
#include <optional>
#include <vector>

#include "component/componenttype.hh"
#include "simulation/simulation.hh"
#include "toplevel/toplevel.hh"
#include "toplevel/board/board.hh"

class Sandbox {
public:
    Sandbox() {
        toplevels_.emplace_back(std::make_unique<Board>(*this));
    }

    void rebuild_simulation() { simulation_.compile(toplevels_); }
    void cycle()              { simulation_.cycle(); }

    [[nodiscard]] std::vector<std::unique_ptr<TopLevel>> const& toplevels() const { return toplevels_; }
    [[nodiscard]] std::optional<TopLevel*> topmost_toplevel_in_pos(ssize_t x, ssize_t y) const;

    void bring_to_front(TopLevel* toplevel);

    [[nodiscard]] std::vector<ComponentType*> const& component_types() const { return component_types_; }

private:
    std::vector<std::unique_ptr<TopLevel>> toplevels_;
    std::vector<ComponentType*>            component_types_ = default_component_types;
    Simulation                             simulation_;
};

#endif //SANDBOX_HH
