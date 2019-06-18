#include "IPAddress.hpp"

IPAddress::IPAddress(const std::string & addr)
{
    std::vector<std::string> splitted;
    std::vector<addr_t> addr_bytes;
    size_t begin_pos = 0;

    while(begin_pos != std::string::npos)
    {
        size_t end_pos = addr.find(".", begin_pos);

        if(end_pos != std::string::npos)
        {
            splitted.push_back(addr.substr(begin_pos, end_pos - begin_pos));
            begin_pos = end_pos + 1;
        }
        else
        {
            splitted.push_back(addr.substr(begin_pos));
            begin_pos = end_pos;
        }
    }

    if(splitted.size() != 4)
        throw std::invalid_argument("Parameter is not a valid IP adress");

    if(std::any_of(splitted.begin(), splitted.end(), [](const std::string & s) {
           return std::any_of(s.begin(), s.end(), [](char c) { return c < '0' || c > '9'; });
       }))
        throw std::invalid_argument("Parameter is not a valid IP adress");

    addr_bytes.resize(splitted.size());
    std::transform(splitted.begin(), splitted.end(), addr_bytes.begin(),
                   [](const std::string & s) { return stoul(s); });

    if(std::any_of(addr_bytes.begin(), addr_bytes.end(), [](addr_t p) { return p > 255; }))
        throw std::invalid_argument("Parameter is not a valid IP adress");

    this->address = std::accumulate(addr_bytes.begin(), addr_bytes.end(), 0,
                                    [](addr_t acc, addr_t b) { return (acc << 8) | b; });
}

IPAddress::operator std::string() const
{
    return std::to_string((address & 0xFF000000) >> 24) + "."
           + std::to_string((address & 0x00FF0000) >> 16) + "."
           + std::to_string((address & 0x0000FF00) >> 8) + "."
           + std::to_string(address & 0x000000FF);
}

std::ostream & operator<<(std::ostream & os, const IPAddress & addr)
{
    os << static_cast<std::string>(addr);

    return os;
}
