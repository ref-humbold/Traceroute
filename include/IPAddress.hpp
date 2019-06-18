#ifndef _IP_ADDRESS_HPP_
#define _IP_ADDRESS_HPP_

#include <cstdlib>
#include <exception>
#include <iostream>
#include <stdexcept>
#include <algorithm>
#include <string>
#include <tuple>
#include <vector>
#include <numeric>

using addr_t = unsigned int;

class IPAddress
{
public:
    explicit IPAddress(addr_t addr) : address{addr}
    {
    }

    explicit IPAddress(const std::string & addr);

    friend bool operator==(const IPAddress & addr1, const IPAddress & addr2);
    friend bool operator<(const IPAddress & addr1, const IPAddress & addr2);
    friend std::ostream & operator<<(std::ostream & os, const IPAddress & addr);

    explicit operator addr_t() const
    {
        return address;
    }

    explicit operator std::string() const;

private:
    addr_t address;
};

inline bool operator==(const IPAddress & addr1, const IPAddress & addr2)
{
    return addr1.address == addr2.address;
}

inline bool operator!=(const IPAddress & addr1, const IPAddress & addr2)
{
    return !(addr1 == addr2);
}

inline bool operator<(const IPAddress & addr1, const IPAddress & addr2)
{
    return addr1.address < addr2.address;
}

inline bool operator<=(const IPAddress & addr1, const IPAddress & addr2)
{
    return (addr1 < addr2) || (addr1 == addr2);
}

inline bool operator>(const IPAddress & addr1, const IPAddress & addr2)
{
    return !(addr1 <= addr2);
}

inline bool operator>=(const IPAddress & addr1, const IPAddress & addr2)
{
    return !(addr1 < addr2);
}

std::ostream & operator<<(std::ostream & os, const IPAddress & addr);

#endif
