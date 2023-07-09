#ifndef ICMP_CONTROLLER_HPP_
#define ICMP_CONTROLLER_HPP_

#include <cstdlib>
#include <iostream>
#include <map>
#include <vector>
#include "SocketReceiver.hpp"
#include "SocketSender.hpp"

#pragma region EchoReply

struct EchoReply
{
    EchoReply() : average_time{0.0}, received_count{0}
    {
    }

    void add(IPv4Address addr, size_t time_ms);

    std::map<IPv4Address, std::vector<size_t>> address_times;
    double average_time;
    size_t received_count;
};

std::ostream & operator<<(std::ostream & os, const EchoReply & reply);

#pragma endregion
#pragma region ICMPController

class ICMPController
{
public:
    explicit ICMPController(const RawSocket & s)
        : socket{s}, sender{SocketSender(s)}, receiver{SocketReceiver(s)}
    {
    }

    void echo_request(const IPv4Address & address, uint16_t id, uint16_t ttl);
    EchoReply echo_reply(uint16_t id, uint16_t ttl);

    const uint16_t attempts = 3;

private:
    IPv4Address receive_echo(uint16_t id, uint16_t ttl);
    uint16_t count_checksum(const uint16_t * header, size_t length);
    icmphdr prepare_icmp(uint16_t id, uint16_t seq);
    std::tuple<const iphdr *, const icmphdr *, const uint8_t *>
            extract_headers(const uint8_t * ptr);

    const RawSocket & socket;
    SocketSender sender;
    SocketReceiver receiver;
};

#pragma endregion
#endif
