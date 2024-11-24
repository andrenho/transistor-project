#include "sandbox.hh"

#include <ranges>
namespace r = std::ranges;

std::optional<TopLevel*> Sandbox::topmost_toplevel_in_pos(ssize_t x, ssize_t y) const
{
    for (auto const& toplevel: toplevels_)
        if (x >= toplevel->position_x && y >= toplevel->position_y
                && x < (toplevel->position_x + (toplevel->w() * toplevel->zoom))
                && y < (toplevel->position_y + (toplevel->h() * toplevel->zoom)))
            return toplevel.get();
    return {};
}

void Sandbox::bring_to_front(TopLevel* toplevel)
{
    auto it = r::find_if(toplevels_, [&toplevel](auto const& t) { return t.get() == toplevel; });
    if (it != toplevels_.end())
        std::rotate(toplevels_.begin(), it, it + 1);
}