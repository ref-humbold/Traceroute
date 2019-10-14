#include "IPAddress.hpp"
#include <exception>
#include <stdexcept>
#include <algorithm>
#include <numeric>

std::vector<std::string> split(const std::string & st)
{
    std::vector<std::string> split_st;
    size_t begin_pos = 0;

    while(begin_pos != std::string::npos)
    {
        size_t end_pos = st.find('.', begin_pos);

        if(end_pos != std::string::npos)
        {
            split_st.push_back(st.substr(begin_pos, end_pos - begin_pos));
            begin_pos = end_pos + 1;
        }
        else
        {
            split_st.push_back(st.substr(begin_pos));
            begin_pos = end_pos;
        }
    }

    return split_st;
}

IPAddress::IPAddress(const std::string & st)
{
    std::vector<std::string> split_st = split(st);
    std::vector<addr_t> addr_bytes;

    if(split_st.size() != 4)
        throw std::invalid_argument("Parameter is not a valid IP address");

    if(std::any_of(split_st.begin(), split_st.end(), [](const std::string & s) {
           return std::any_of(s.begin(), s.end(), [](char c) { return c < '0' || c > '9'; });
       }))
        throw std::invalid_argument("Parameter is not a valid IP address");

    addr_bytes.resize(split_st.size());
    std::transform(split_st.begin(), split_st.end(), addr_bytes.begin(),
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

std::vector<unsigned int> IPAddress::quadruple() const
{
    return std::vector<unsigned int>({(address & 0xFF000000U) >> 24U,
                                      (address & 0x00FF0000U) >> 16U, (address & 0x0000FF00U) >> 8U,
                                      address & 0x000000FFU});
}

std::ostream & operator<<(std::ostream & os, const IPAddress & a)
{
    std::vector<unsigned int> q = a.quadruple();

    os << q[0] << "." << q[1] << "." << q[2] << "." << q[3];

    return os;
}
