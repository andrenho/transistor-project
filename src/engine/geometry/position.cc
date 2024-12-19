#include "position.hh"

#include "exceptions/deserializationerror.hh"

std::string Position::serialize() const
{
    return std::to_string(x) + "," + std::to_string(y);
}

Position Position::deserialize(std::string const& str)
{
    auto find = str.find(',');
    if (find == std::string::npos) throw DeserializationError();
    return {
        .x = std::stoi(str.substr(0, find - 1)),
        .y = std::stoi(str.substr(find + 1))
    };
}