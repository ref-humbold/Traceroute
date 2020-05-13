#ifndef IP_ADDRESS_HPP_
#define IP_ADDRESS_HPP_

#include <cstdlib>
#include <cinttypes>
#include <iostream>
#include <string>
#include <vector>

class IPAddress
{
public:
    using addr_t = uint32_t;

    explicit IPAddress(addr_t a) : address{a}
    {
    }

    explicit IPAddress(const std::string & st);

    IPAddress(const IPAddress & a) = default;
    IPAddress(IPAddress && a) = default;
    IPAddress & operator=(const IPAddress & a) = default;
    IPAddress & operator=(IPAddress && a) = default;

    friend bool operator==(const IPAddress & a1, const IPAddress & a2);
    friend bool operator<(const IPAddress & a1, const IPAddress & a2);
    friend std::ostream & operator<<(std::ostream & os, const IPAddress & a);

    explicit operator addr_t() const
    {
        return address;
    }

    explicit operator std::string() const;

private:
    std::vector<unsigned int> quadruple() const;

    addr_t address;
};

inline bool operator==(const IPAddress & a1, const IPAddress & a2)
{
    return a1.address == a2.address;
}

inline bool operator!=(const IPAddress & a1, const IPAddress & a2)
{
    return !(a1 == a2);
}

inline bool operator<(const IPAddress & a1, const IPAddress & a2)
{
    return a1.address < a2.address;
}

inline bool operator<=(const IPAddress & a1, const IPAddress & a2)
{
    return (a1 < a2) || (a1 == a2);
}

inline bool operator>(const IPAddress & a1, const IPAddress & a2)
{
    return !(a1 <= a2);
}

inline bool operator>=(const IPAddress & a1, const IPAddress & a2)
{
    return !(a1 < a2);
}

std::ostream & operator<<(std::ostream & os, const IPAddress & addr);

#endif
