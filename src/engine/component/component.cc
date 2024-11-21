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
