#ifndef ICMP_CONTROLLER_HPP_
#define ICMP_CONTROLLER_HPP_

#include <cstdlib>
#include <iostream>
#include <set>
#include "SocketReceiver.hpp"
#include "SocketSender.hpp"

struct EchoReply
{
    EchoReply(const std::set<IPAddress> & addresses, size_t average_time, size_t received_count)
        : addresses{addresses}, average_time{average_time}, received_count{received_count}
    {
    }

    std::set<IPAddress> addresses;
    size_t average_time;
    size_t received_count;
};

std::ostream & operator<<(std::ostream & os, const EchoReply & reply);

class ICMPController
{
public:
    explicit ICMPController(RawSocket & s)
        : socket{s}, sender{SocketSender(s)}, receiver{SocketReceiver(s)}
    {
    }

    void echo_request(const IPAddress & address, uint16_t id, uint16_t ttl);
    EchoReply echo_reply(uint16_t id, uint16_t ttl);

    const uint16_t attempts = 3;

private:
    IPAddress receive_echo(uint16_t id, uint16_t ttl);
    uint16_t count_checksum(const uint16_t * header, size_t length);
    icmphdr prepare_icmp(uint16_t id, uint16_t seq);
    std::tuple<const iphdr *, const icmphdr *, const uint8_t *>
            extract_headers(const uint8_t * ptr);

    const RawSocket & socket;
    SocketSender sender;
    SocketReceiver receiver;
};

#endif
