#include "component.hh"

#include <iostream>

#include "exceptions/deserializationerror.hh"

std::unique_ptr<Component> Component::deserialize(std::vector<ComponentType*> const& supported_component_types,
                                                  std::string const& serial)
{
    for (ComponentType* ct: supported_component_types) {
        if (serial.starts_with(ct->id + ":")) {
            auto substr = serial.substr(serial.find(':') + 1);
            return ct->create_component_from_serial(substr);
        }
    }

    std::cerr << "Unsupported component: " << serial << "\n";
    throw DeserializationError();
}

std::vector<SubPosition> Component::pin_relative_positions() const
{
    auto const& pc = type->physical_characteristics;

    // TODO - right now, only 1x1 components are supported
    if (pc.size_w != 1 || pc.size_h != 1)
        throw std::runtime_error("Sorry, only 1x1 components are supported by now.");

    // create pins
    std::vector<SubPosition> subpositions;
    for (auto const& pin_config: type->physical_characteristics.pins) {
        if (SubPosition const* sp = std::get_if<SubPosition>(&pin_config.pos); sp) {
            subpositions.push_back(*sp);
        } else if (Position const* pos = std::get_if<Position>(&pin_config.pos); pos) {
            subpositions.push_back({ *pos, Direction::N });
            subpositions.push_back({ *pos, Direction::E });
            subpositions.push_back({ *pos, Direction::S });
            subpositions.push_back({ *pos, Direction::W });
        }
    }

    // rotate pins
    uint8_t rot_times = 0;
    if (direction_ == Direction::E)
        rot_times = 1;
    else if (direction_ == Direction::S)
        rot_times = 2;
    else if (direction_ == Direction::W)
        rot_times = 3;

    for (uint8_t i = 0; i < rot_times; ++i)
        for (SubPosition& sp: subpositions)
            sp.dir = ::rotate(sp.dir);

    return subpositions;
}
