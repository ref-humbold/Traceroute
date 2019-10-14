#ifndef ICMP_CONTROLLER_HPP_
#define ICMP_CONTROLLER_HPP_

#include <cstdlib>
#include <set>
#include <tuple>
#include "ICMPReceiver.hpp"
#include "ICMPSender.hpp"

class ICMPController
{
    const RawSocket & socket;
    ICMPSender sender;
    ICMPReceiver receiver;

public:
    explicit ICMPController(RawSocket & s)
        : socket{s}, sender{ICMPSender(s)}, receiver{ICMPReceiver(s)}
    {
    }

    void echo_request(const IPAddress & addr, uint16_t id, uint16_t ttl);
    std::tuple<std::set<IPAddress>, size_t, size_t> echo_reply(uint16_t id, uint16_t ttl);

private:
    IPAddress recv_echo(uint16_t id, uint16_t ttl);
};

#endif
