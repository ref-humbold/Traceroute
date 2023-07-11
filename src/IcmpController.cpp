#include "IcmpController.hpp"
#include <cerrno>
#include <cstring>
#include <ctime>
#include <string>
#include <tuple>

#pragma region EchoReply

void EchoReply::add(Ip4Address addr, size_t time_ms)
{
    address_times.emplace(addr, std::vector<size_t>());
    address_times[addr].push_back(time_ms);
    ++received_count;
    average_time += (time_ms - average_time) / received_count;
}

std::ostream & operator<<(std::ostream & os, const EchoReply & reply)
{
    if(reply.address_times.empty())
    {
        os << "*";
        return os;
    }

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
    return os;
}

#pragma endregion
#pragma region IcmpController

void IcmpController::echo_request(const Ip4Address & address, uint16_t id, uint16_t ttl)
{
    for(uint16_t i = 0; i < attempts; ++i)
    {
        icmphdr icmp_header = prepare_icmp(id, attempts * ttl + i);

        sender.address(address).ttl(ttl).send(&icmp_header, sizeof(icmp_header));
    }
}

EchoReply IcmpController::echo_reply(uint16_t id, uint16_t ttl)
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

        std::optional<Ip4Address> address = receive_echo(id, ttl);

        if(!address)
            continue;

        reply.add(*address, (1000000 - timer.tv_usec) / 1000);
    } while(reply.received_count < attempts);

    return reply;
}

uint16_t IcmpController::count_checksum(const uint16_t * header, size_t length)
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

icmphdr IcmpController::prepare_icmp(uint16_t id, uint16_t seq)
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
        IcmpController::extract_headers(const uint8_t * ptr)
{
    const iphdr * header_ip = reinterpret_cast<const iphdr *>(ptr);
    const icmphdr * header_icmp = reinterpret_cast<const icmphdr *>(ptr + 4U * header_ip->ihl);
    const uint8_t * body = ptr + 4U * header_ip->ihl + sizeof(icmphdr);

    return std::make_tuple(header_ip, header_icmp, body);
}

std::optional<Ip4Address> IcmpController::receive_echo(uint16_t id, uint16_t ttl)
{
    SocketReceiver::Message message = receiver.receive();
    const iphdr * header_ip;
    const icmphdr * header_icmp;
    const uint8_t * body;

    std::tie(header_ip, header_icmp, body) = extract_headers(message.message().data());

    if(header_icmp->type == 0)
    {
        if(header_icmp->un.echo.id != id || header_icmp->un.echo.sequence / attempts != ttl)
            return std::nullopt;
    }
    else if(header_icmp->type == 11)
    {
        const iphdr * header_ip_body;
        const icmphdr * header_icmp_body;

        std::tie(header_ip_body, header_icmp_body, std::ignore) = extract_headers(body);

        if(header_icmp_body->un.echo.id != id
           || header_icmp_body->un.echo.sequence / attempts != ttl)
            return std::nullopt;
    }

    return std::make_optional(message.address());
}

#pragma endregion
