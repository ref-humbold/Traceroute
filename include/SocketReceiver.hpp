#ifndef SOCKET_RECEIVER_HPP_
#define SOCKET_RECEIVER_HPP_

#include <cstdlib>
#include <vector>
#include <arpa/inet.h>
#include <netinet/ip_icmp.h>
#include "IPv4Address.hpp"
#include "RawSocket.hpp"

class SocketReceiver
{
public:
    class Message;

    explicit SocketReceiver(const RawSocket & s) : socket{s}
    {
    }

    Message receive() const;

private:
    const RawSocket & socket;
};

class SocketReceiver::Message
{
public:
    Message(const sockaddr_in & address, const std::vector<uint8_t> & message)
        : address_{address}, message_{message}
    {
    }

    IPv4Address address() const;

    const std::vector<uint8_t> & message() const
    {
        return message_;
    }

private:
    sockaddr_in address_;
    std::vector<uint8_t> message_;
};

#endif
