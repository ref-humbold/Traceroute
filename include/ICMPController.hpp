#ifndef ICMP_CONTROLLER_HPP_
#define ICMP_CONTROLLER_HPP_

#include <cstdlib>
#include <set>
#include <tuple>
#include "SocketReceiver.hpp"
#include "SocketSender.hpp"

class ICMPController
{
public:
    explicit ICMPController(RawSocket & s)
        : socket{s}, sender{SocketSender(s)}, receiver{SocketReceiver(s)}
    {
    }

    void echo_request(const IPAddress & addr, uint16_t id, uint16_t ttl);
    std::tuple<std::set<IPAddress>, size_t, size_t> echo_reply(uint16_t id, uint16_t ttl);

private:
    IPAddress recv_echo(uint16_t id, uint16_t ttl);

    const RawSocket & socket;
    SocketSender sender;
    SocketReceiver receiver;
};

#endif
