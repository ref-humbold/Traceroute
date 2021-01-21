#ifndef IP_ADDRESS_HPP_
#define IP_ADDRESS_HPP_

#include <cinttypes>
#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>

class IPAddress
{
public:
    using addr_t = uint32_t;

    explicit IPAddress(addr_t address) : address{address}
    {
    }

    explicit IPAddress(const std::string & str);

    IPAddress(const IPAddress &) = default;
    IPAddress(IPAddress &&) = default;
    IPAddress & operator=(const IPAddress &) = default;
    IPAddress & operator=(IPAddress &&) = default;

    friend bool operator==(const IPAddress & a1, const IPAddress & a2);
    friend bool operator<(const IPAddress & a1, const IPAddress & a2);
    friend std::ostream & operator<<(std::ostream & os, const IPAddress & a);

    explicit operator addr_t() const
    {
        return address;
    }

    explicit operator std::string() const;

private:
    std::vector<addr_t> quadruple() const;
    std::vector<std::string> split(const std::string & str) const;

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

inline std::ostream & operator<<(std::ostream & os, const IPAddress & addr)
{
    std::vector<IPAddress::addr_t> q = addr.quadruple();

    os << q[0] << "." << q[1] << "." << q[2] << "." << q[3];
    return os;
}

#endif
