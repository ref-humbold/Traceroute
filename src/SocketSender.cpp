#include "SocketSender.hpp"
#include <cerrno>
#include <cstring>
#include <string>

void SocketSender::send(const void * message_buffer, int message_size) const
{
    setsockopt(socket.descriptor(), IPPROTO_IP, IP_TTL, &ttl_, sizeof(uint16_t));

    ssize_t sent_size = sendto(socket.descriptor(), message_buffer, message_size, 0,
                               reinterpret_cast<const sockaddr *>(&address_), sizeof(address_));

    if(sent_size < 0)
        throw SocketException(strerror(errno));
}

SocketSender & SocketSender::address(const IPv4Address & addr)
{
    address_.sin_family = AF_INET;

    std::string address_str = std::string(addr);
    int result = inet_pton(AF_INET, address_str.c_str(), &address_.sin_addr);

    if(result < 1)
        throw SocketException("Invalid address " + address_str);

    return *this;
}
