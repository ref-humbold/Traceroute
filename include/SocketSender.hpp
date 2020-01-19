#ifndef SOCKET_SENDER_HPP_
#define SOCKET_SENDER_HPP_

#include <cstdlib>
#include <cinttypes>
#include <arpa/inet.h>
#include <netinet/ip_icmp.h>
#include "IPAddress.hpp"
#include "RawSocket.hpp"

class SocketSender
{
private:
    const RawSocket & socket;
    sockaddr_in receiver_address;

public:
    explicit SocketSender(RawSocket & s) : socket{s}, receiver_address{}
    {
    }

    void send(const void * msg_buf, int msg_size, uint16_t ttl);
    void set_receiver(const IPAddress & addr);
};

#endif
