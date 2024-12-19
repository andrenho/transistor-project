#ifndef WIREMANAGEMENT_HH
#define WIREMANAGEMENT_HH

#include <optional>

#include "wireconfiguration.hh"
#include "engine/geometry/position.hh"

class WireManagement {
public:
    void    start_drawing(Position const& pos, WireWidth width, WireLayer side);
    void    set_current_end(Position const& pos);
    WireMap stop_drawing(Position const& pos);

    void    set_orientation(Orientation orientation) { if (drawing_wire_) drawing_wire_->orientation = orientation; }

    [[nodiscard]] WireMap current_drawing() const;

private:
    struct TempWire {
        Position                   start_pos;
        Position                   end_pos;
        WireWidth                  width;
        WireLayer                   side;
        std::optional<Orientation> orientation {};
    };
    std::optional<TempWire> drawing_wire_;
};

#endif //WIREMANAGEMENT_HH
