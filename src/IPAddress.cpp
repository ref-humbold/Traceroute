#include "IPAddress.hpp"
#include <algorithm>
#include <exception>
#include <numeric>
#include <stdexcept>

IPAddress::IPAddress(const std::string & str)
{
    std::vector<std::string> split_str = split(str);
    std::vector<addr_t> addr_bytes;

    if(split_str.size() != 4)
        throw std::invalid_argument("Parameter is not a valid IP address");

    if(std::any_of(split_str.begin(), split_str.end(), [](const std::string & s) {
           return std::any_of(s.begin(), s.end(), [](char c) { return c < '0' || c > '9'; });
       }))
        throw std::invalid_argument("Parameter is not a valid IP address");

    std::transform(split_str.begin(), split_str.end(), std::back_inserter(addr_bytes),
                   [](const std::string & s) { return stoul(s); });

    if(std::any_of(addr_bytes.begin(), addr_bytes.end(), [](addr_t p) { return p > 255; }))
        throw std::invalid_argument("Parameter is not a valid IP address");

    address = std::accumulate(addr_bytes.begin(), addr_bytes.end(), 0,
                              [](addr_t acc, addr_t b) { return (acc << 8U) | b; });
}

IPAddress::operator std::string() const
{
    std::vector<IPAddress::addr_t> q = quadruple();

    return std::to_string(q[0]) + "." + std::to_string(q[1]) + "." + std::to_string(q[2]) + "."
           + std::to_string(q[3]);
}

std::vector<IPAddress::addr_t> IPAddress::quadruple() const
{
    return {(address & 0xFF000000U) >> 24U, (address & 0x00FF0000U) >> 16U,
            (address & 0x0000FF00U) >> 8U, address & 0x000000FFU};
}

std::vector<std::string> IPAddress::split(const std::string & str) const
{
    std::vector<std::string> split_str;
    size_t begin_pos = 0;

    while(begin_pos != std::string::npos)
    {
        size_t end_pos = str.find('.', begin_pos);

        if(end_pos != std::string::npos)
        {
            split_str.push_back(str.substr(begin_pos, end_pos - begin_pos));
            begin_pos = end_pos + 1;
        }
        else
        {
            split_str.push_back(str.substr(begin_pos));
            begin_pos = end_pos;
        }
    }

    return split_str;
}
