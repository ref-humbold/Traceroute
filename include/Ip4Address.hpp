#ifndef IP4_ADDRESS_HPP_
#define IP4_ADDRESS_HPP_

#include <cinttypes>
#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>

class Ip4Address
{
public:
    using addr_t = uint32_t;

    explicit Ip4Address(addr_t address) : address{address}
    {
    }

    explicit Ip4Address(const std::string & str);

    Ip4Address(const Ip4Address &) = default;
    Ip4Address(Ip4Address &&) = default;
    Ip4Address & operator=(const Ip4Address &) = default;
    Ip4Address & operator=(Ip4Address &&) = default;

    friend bool operator==(const Ip4Address & a1, const Ip4Address & a2);
    friend bool operator<(const Ip4Address & a1, const Ip4Address & a2);
    friend std::ostream & operator<<(std::ostream & os, const Ip4Address & a);

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

inline bool operator==(const Ip4Address & a1, const Ip4Address & a2)
{
    return a1.address == a2.address;
}

inline bool operator!=(const Ip4Address & a1, const Ip4Address & a2)
{
    return !(a1 == a2);
}

inline bool operator<(const Ip4Address & a1, const Ip4Address & a2)
{
    return a1.address < a2.address;
}

inline bool operator<=(const Ip4Address & a1, const Ip4Address & a2)
{
    return (a1 < a2) || (a1 == a2);
}

inline bool operator>(const Ip4Address & a1, const Ip4Address & a2)
{
    return !(a1 <= a2);
}

inline bool operator>=(const Ip4Address & a1, const Ip4Address & a2)
{
    return !(a1 < a2);
}

inline std::ostream & operator<<(std::ostream & os, const Ip4Address & addr)
{
    std::vector<Ip4Address::addr_t> q = addr.quadruple();

    os << q[0] << "." << q[1] << "." << q[2] << "." << q[3];
    return os;
}

#endif
