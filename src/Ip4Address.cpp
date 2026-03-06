#include "Ip4Address.hpp"
#include <numeric>
#include <regex>
#include <stdexcept>

Ip4Address::operator std::string() const
{
    std::array<address_t, 4> q = quadruple();

    return std::to_string(q[0]) + "." + std::to_string(q[1]) + "." + std::to_string(q[2]) + "."
           + std::to_string(q[3]);
}

uint32_t Ip4Address::parse(const std::string & str)
{
    std::regex ip_regex(R"=((\d{1,3})\.(\d{1,3})\.(\d{1,3})\.(\d{1,3}))=");
    std::regex number_regex(R"=(\d|[1-9]\d|1\d\d|2[0-4]\d|25[0-5])=");
    std::smatch ip_match;

    std::regex_match(str, ip_match, ip_regex);

    if(ip_match.size() != 5)
        throw std::invalid_argument("Parameter is not a valid IP address");

    std::vector<address_t> addr_bytes;

    for(auto match = ip_match.begin() + 1; match != ip_match.end(); ++match)
    {
        if(!std::regex_match(match->str(), number_regex))
            throw std::invalid_argument("Parameter is not a valid IP address");

        addr_bytes.push_back(stoul(match->str()));
    }

    return std::accumulate(addr_bytes.begin(), addr_bytes.end(), 0,
            [](address_t acc, address_t b) { return (acc << 8U) | b; });
}

std::array<Ip4Address::address_t, 4> Ip4Address::quadruple() const
{
    return {(address & 0xFF000000U) >> 24U, (address & 0x00FF0000U) >> 16U,
        (address & 0x0000FF00U) >> 8U, address & 0x000000FFU};
}

std::ostream & operator<<(std::ostream & os, const Ip4Address & addr)
{
    std::array<Ip4Address::address_t, 4> q = addr.quadruple();

    os << q[0] << "." << q[1] << "." << q[2] << "." << q[3];
    return os;
}
