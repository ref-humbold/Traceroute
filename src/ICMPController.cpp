#include "ICMPController.hpp"
#include <cerrno>
#include <cstring>
#include <ctime>
#include <string>

uint16_t count_checksum(const uint16_t * hdr, size_t length)
{
    if(length % 2 == 1)
        throw SocketException("Incorrect length of ICMP header.");

    uint32_t sum = 0;
    const uint16_t * ptr = hdr;

    for(size_t i = 0; i < length; i += 2)
    {
        sum += *ptr;
        ++ptr;
    }

    sum = (sum >> 16U) + (sum & 0xFFFFU);
    return static_cast<uint16_t>(~(sum + (sum >> 16U)));
}

icmphdr prepare_icmp(uint16_t id, uint16_t seq)
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

std::tuple<iphdr *, icmphdr *, uint8_t *> extract_headers(uint8_t * ptr)
{
    iphdr * hIP = reinterpret_cast<iphdr *>(ptr);
    icmphdr * hICMP = reinterpret_cast<icmphdr *>(ptr + 4U * hIP->ihl);
    uint8_t * body = ptr + 4U * hIP->ihl + sizeof(icmphdr);

    return std::make_tuple(hIP, hICMP, body);
}

std::ostream & operator<<(std::ostream & os, const EchoReply & reply)
{
    if(reply.addresses.empty())
        os << "*";
    else
    {
        for(auto addr : reply.addresses)
            os << addr << " ";

        os << "-- " << reply.average_time / 1000 << " ms (" << reply.received_count << ")";
    }

    return os;
}

void ICMPController::echo_request(const IPAddress & addr, uint16_t id, uint16_t ttl)
{
    for(uint16_t i = 0; i < attempts; ++i)
    {
        icmphdr header = prepare_icmp(id, attempts * ttl + i);

        sender.set_receiver(addr);
        sender.send(&header, sizeof(header), ttl);
    }
}

EchoReply ICMPController::echo_reply(uint16_t id, uint16_t ttl)
{
    std::set<IPAddress> recv_addr;
    fd_set fd;
    timeval timer = {};
    size_t avg_time = 0;
    size_t recv_num = 0;

    FD_ZERO(&fd);
    FD_SET(socket.descriptor(), &fd);
    timer.tv_sec = 1;
    timer.tv_usec = 0;

    do
    {
        int ready = select(socket.descriptor() + 1, &fd, nullptr, nullptr, &timer);

        if(ready < 0)
            throw SocketException(strerror(errno));

        if(ready == 0)
            break;

        IPAddress address = recv_echo(id, ttl);

        if(address == IPAddress(0))
            continue;

        recv_addr.insert(address);
        avg_time = (avg_time + 1000000 - timer.tv_usec) / 2;
        ++recv_num;
    } while(recv_num < 3);

    return EchoReply(recv_addr, avg_time, recv_num);
}

IPAddress ICMPController::recv_echo(uint16_t id, uint16_t ttl)
{
    std::vector<uint8_t> message = receiver.receive();
    iphdr * hIP;
    icmphdr * hICMP;
    uint8_t * body;

    std::tie(hIP, hICMP, body) = extract_headers(message.data());

    if(hICMP->type == 0)
    {
        if(hICMP->un.echo.id != id || hICMP->un.echo.sequence / 3 != ttl)
            return IPAddress(0);
    }
    else if(hICMP->type == 11)
    {
        iphdr * hIP_body;
        icmphdr * hICMP_body;

        std::tie(hIP_body, hICMP_body, std::ignore) = extract_headers(body);

        if(hICMP_body->un.echo.id != id || hICMP_body->un.echo.sequence / 3 != ttl)
            return IPAddress(0);
    }

    return receiver.take_address();
}
