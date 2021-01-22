#ifndef ICMP_CONTROLLER_HPP_
#define ICMP_CONTROLLER_HPP_

#include <cstdlib>
#include <iostream>
#include <map>
#include <vector>
#include "SocketReceiver.hpp"
#include "SocketSender.hpp"

struct EchoReply
{
    EchoReply() : average_time{0.0}, received_count{0}
    {
    }

    void add(IPAddress addr, size_t time_ms)
    {
        address_times.emplace(addr, std::vector<size_t>());
        address_times[addr].push_back(time_ms);
        ++received_count;
        average_time += (time_ms - average_time) / received_count;
    }

    std::map<IPAddress, std::vector<size_t>> address_times;
    double average_time;
    size_t received_count;
};

std::ostream & operator<<(std::ostream & os, const EchoReply & reply);

class ICMPController
{
public:
    explicit ICMPController(const RawSocket & s)
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
