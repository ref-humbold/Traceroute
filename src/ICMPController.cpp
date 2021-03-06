#include "ICMPController.hpp"
#include <cerrno>
#include <cstring>
#include <ctime>
#include <string>
#include <tuple>

std::ostream & operator<<(std::ostream & os, const EchoReply & reply)
{
    if(reply.address_times.empty())
        os << "*";
    else
    {
        std::string address_separator = "";

        for(auto && addr_time : reply.address_times)
        {
            std::string time_separator = "";

            os << address_separator << addr_time.first << " -- ";

            for(auto && resp_time : addr_time.second)
            {
                os << time_separator << resp_time << " ms";
                time_separator = ", ";
            }

            address_separator = " / ";
        }

        os << " (avg " << reply.average_time << " ms)";
    }

    return os;
}

void ICMPController::echo_request(const IPAddress & address, uint16_t id, uint16_t ttl)
{
    for(uint16_t i = 0; i < attempts; ++i)
    {
        icmphdr icmp_header = prepare_icmp(id, attempts * ttl + i);

        sender.address(address).ttl(ttl).send(&icmp_header, sizeof(icmp_header));
    }
}

EchoReply ICMPController::echo_reply(uint16_t id, uint16_t ttl)
{
    EchoReply reply;
    fd_set fd;
    timeval timer = {.tv_sec = 1, .tv_usec = 0};

    FD_ZERO(&fd);
    FD_SET(socket.descriptor(), &fd);

    do
    {
        int ready = select(socket.descriptor() + 1, &fd, nullptr, nullptr, &timer);

        if(ready < 0)
            throw SocketException(strerror(errno));

        if(ready == 0)
            break;

        IPAddress address = receive_echo(id, ttl);

        if(address == IPAddress(0))
            continue;

        reply.add(address, (1000000 - timer.tv_usec) / 1000);
    } while(reply.received_count < attempts);

    return reply;
}

uint16_t ICMPController::count_checksum(const uint16_t * header, size_t length)
{
    if(length % 2 == 1)
        throw SocketException("Incorrect length of ICMP header");

    uint32_t sum = 0;
    const uint16_t * ptr = header;

    for(size_t i = 0; i < length; i += 2)
    {
        sum += *ptr;
        ++ptr;
    }

    sum = (sum >> 16U) + (sum & 0xFFFFU);
    return static_cast<uint16_t>(~(sum + (sum >> 16U)));
}

icmphdr ICMPController::prepare_icmp(uint16_t id, uint16_t seq)
{
    icmphdr header = {};
    header.type = ICMP_ECHO;
    header.code = 0;
    header.un.echo.id = id;
    header.un.echo.sequence = seq;
    header.checksum = 0;
    header.checksum = count_checksum(reinterpret_cast<uint16_t *>(&header), sizeof(header));
    return header;
}

std::tuple<const iphdr *, const icmphdr *, const uint8_t *>
        ICMPController::extract_headers(const uint8_t * ptr)
{
    const iphdr * hIP = reinterpret_cast<const iphdr *>(ptr);
    const icmphdr * hICMP = reinterpret_cast<const icmphdr *>(ptr + 4U * hIP->ihl);
    const uint8_t * body = ptr + 4U * hIP->ihl + sizeof(icmphdr);

    return std::make_tuple(hIP, hICMP, body);
}

IPAddress ICMPController::receive_echo(uint16_t id, uint16_t ttl)
{
    SocketReceiver::Message message = receiver.receive();
    const iphdr * hIP;
    const icmphdr * hICMP;
    const uint8_t * body;

    std::tie(hIP, hICMP, body) = extract_headers(message.message().data());

    if(hICMP->type == 0)
    {
        if(hICMP->un.echo.id != id || hICMP->un.echo.sequence / attempts != ttl)
            return IPAddress(0);
    }
    else if(hICMP->type == 11)
    {
        const iphdr * hIP_body;
        const icmphdr * hICMP_body;

        std::tie(hIP_body, hICMP_body, std::ignore) = extract_headers(body);

        if(hICMP_body->un.echo.id != id || hICMP_body->un.echo.sequence / attempts != ttl)
            return IPAddress(0);
    }

    return message.address();
}
