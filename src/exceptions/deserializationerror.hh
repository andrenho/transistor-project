#ifndef DESERIALIZATIONERROR_HH
#define DESERIALIZATIONERROR_HH

#include <stdexcept>

class DeserializationError : public std::runtime_error {
public:
    DeserializationError() : std::runtime_error("Deserialization error") {}
};

#endif //DESERIALIZATIONERROR_HH
