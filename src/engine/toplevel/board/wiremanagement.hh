#ifndef WIREMANAGEMENT_HH
#define WIREMANAGEMENT_HH

#include "wireconfiguration.hh"
#include "engine/position.hh"

class WireManagement {
public:
    void    start_drawing(Position const& pos);
    void    set_current_end(Position const& pos);
    WireMap stop_drawing(Position const& pos);

    [[nodiscard]] WireMap current_drawing() const;
};

#endif //WIREMANAGEMENT_HH
