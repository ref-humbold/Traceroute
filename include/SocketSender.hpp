#ifndef SOCKET_SENDER_HPP_
#define SOCKET_SENDER_HPP_

#include <cinttypes>
#include <cstdlib>
#include <arpa/inet.h>
#include <netinet/ip_icmp.h>
#include "Ip4Address.hpp"
#include "RawSocket.hpp"

class SocketSender
{
public:
    explicit SocketSender(const RawSocket & s) : socket{s}, address_{}, ttl_{0}
    {
    }

    void send(const void * message_buffer, int message_size) const;
    SocketSender & address(const Ip4Address & addr);

    SocketSender & ttl(uint16_t value)
    {
        ttl_ = value;
        return *this;
    }

private:
    const RawSocket & socket;
    sockaddr_in address_;
    uint16_t ttl_;
};

#endif
