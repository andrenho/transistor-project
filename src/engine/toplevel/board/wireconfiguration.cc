#include "wireconfiguration.hh"

std::string WireConfiguration::serialize() const
{
    return std::string(1, (char) width) + ((char) side) + ((char) dir);
}

WireConfiguration WireConfiguration::deserialize(std::string const& str)
{
    WireConfiguration wc;
    wc.width = (WireWidth) str.at(0);
    wc.side = (WireSide) str.at(1);
    wc.dir = (Direction) str.at(2);
    return wc;
}
