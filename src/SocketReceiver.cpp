#include "SocketReceiver.hpp"
#include <cerrno>
#include <cstring>
#include <algorithm>
#include <string>

SocketReceiver::Message SocketReceiver::receive() const
{
    sockaddr_in address = {};
    socklen_t address_size = sizeof(address);
    uint8_t message_buffer[IP_MAXPACKET];
    ssize_t message_size = recvfrom(socket.descriptor(), message_buffer, IP_MAXPACKET, MSG_DONTWAIT,
                                    reinterpret_cast<sockaddr *>(&address), &address_size);

    if(message_size < 0)
        throw SocketException(strerror(errno));

    return Message(address, std::vector<uint8_t>(std::begin(message_buffer),
                                                 std::begin(message_buffer) + message_size));
}

Ip4Address SocketReceiver::Message::address() const
{
    char ip_str[32];
    const char * result = inet_ntop(AF_INET, &(address_.sin_addr), ip_str, sizeof(ip_str));

    if(result == nullptr)
        throw SocketException(strerror(errno));

    return Ip4Address(std::string(ip_str));
}
