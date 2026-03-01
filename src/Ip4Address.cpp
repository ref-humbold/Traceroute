#include "Ip4Address.hpp"
#include <numeric>
#include <stdexcept>
#include <regex>

Ip4Address::Ip4Address(const std::string & str)
{
    std::regex ip_regex(R"=((\d{1,3})\.(\d{1,3})\.(\d{1,3})\.(\d{1,3}))=");
    std::regex number_regex(R"=(\d|[1-9]\d|1\d\d|2[0-4]\d|25[0-5])=");
    std::smatch ip_match;

    std::regex_match(str, ip_match, ip_regex);

    if(ip_match.size() != 5)
        throw std::invalid_argument("Parameter is not a valid IP address");

    std::vector<addr_t> addr_bytes;

    for(auto match = ip_match.begin() +1; match != ip_match.end(); ++match)
    {
        if(!std::regex_match(match->str(), number_regex))
            throw std::invalid_argument("Parameter is not a valid IP address");

        addr_bytes.push_back(stoul(match->str()));
    }

    address = std::accumulate(addr_bytes.begin(), addr_bytes.end(), 0,
            [](addr_t acc, addr_t b) { return (acc << 8U) | b; });
}

Ip4Address::operator std::string() const
{
    std::vector<Ip4Address::addr_t> q = quadruple();

    return std::to_string(q[0]) + "." + std::to_string(q[1]) + "." + std::to_string(q[2]) + "."
           + std::to_string(q[3]);
}

std::vector<Ip4Address::addr_t> Ip4Address::quadruple() const
{
    return {(address & 0xFF000000U) >> 24U, (address & 0x00FF0000U) >> 16U,
        (address & 0x0000FF00U) >> 8U, address & 0x000000FFU};
}
