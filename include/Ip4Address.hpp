#ifndef IP4_ADDRESS_HPP_
#define IP4_ADDRESS_HPP_

#include <cinttypes>
#include <array>
#include <iostream>
#include <string>

class Ip4Address
{
public:
    using address_t = uint32_t;

    explicit Ip4Address(address_t address) : address{address}
    {
    }

    explicit Ip4Address(const std::string & str) : Ip4Address(parse(str))
    {
    }

    Ip4Address(const Ip4Address &) = default;
    Ip4Address(Ip4Address &&) = default;
    Ip4Address & operator=(const Ip4Address &) = default;
    Ip4Address & operator=(Ip4Address &&) = default;

    friend bool operator==(const Ip4Address & a1, const Ip4Address & a2);
    friend bool operator<(const Ip4Address & a1, const Ip4Address & a2);
    friend std::ostream & operator<<(std::ostream & os, const Ip4Address & a);

    explicit operator address_t() const
    {
        return address;
    }

    explicit operator std::string() const;

private:
    static uint32_t parse(const std::string & str);
    std::array<address_t, 4> quadruple() const;

    address_t address;
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
    return a1 < a2 || a1 == a2;
}

inline bool operator>(const Ip4Address & a1, const Ip4Address & a2)
{
    return !(a1 <= a2);
}

inline bool operator>=(const Ip4Address & a1, const Ip4Address & a2)
{
    return !(a1 < a2);
}

std::ostream & operator<<(std::ostream & os, const Ip4Address & addr);

#endif
