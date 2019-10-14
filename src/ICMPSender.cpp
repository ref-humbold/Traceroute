#include "ICMPSender.hpp"
#include <cerrno>
#include <cstring>
#include <string>

void ICMPSender::send(const void * msg_buf, int msg_size, uint16_t ttl)
{
    setsockopt(socket.descriptor(), IPPROTO_IP, IP_TTL, &ttl, sizeof(uint16_t));

    ssize_t sent_size = sendto(socket.descriptor(), msg_buf, msg_size, 0,
                               (sockaddr *)&receiver_address, sizeof(receiver_address));

    if(sent_size < 0)
        throw SocketException(strerror(errno));
}

void ICMPSender::set_receiver(const IPAddress & addr)
{
    receiver_address.sin_family = AF_INET;

    int result = inet_pton(AF_INET, std::string(addr).c_str(), &receiver_address.sin_addr);

    if(result < 1)
        throw SocketException("Invalid addressing.");
}
