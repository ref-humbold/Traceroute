#ifndef SOCKET_RECEIVER_HPP_
#define SOCKET_RECEIVER_HPP_

#include <cstdlib>
#include <vector>
#include <arpa/inet.h>
#include <netinet/ip_icmp.h>
#include "IPAddress.hpp"
#include "RawSocket.hpp"

class SocketReceiver
{
public:
    explicit SocketReceiver(RawSocket & s) : socket{s}, sender_address{}
    {
    }

    std::vector<uint8_t> receive();
    IPAddress take_address();

private:
    const RawSocket & socket;
    sockaddr_in sender_address;
};

#endif