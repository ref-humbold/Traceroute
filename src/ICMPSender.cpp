#include "ICMPSender.hpp"

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

icmphdr ICMPSender::prepare_icmp(uint16_t id, uint16_t seq)
{
    icmphdr header;

    header.type = ICMP_ECHO;
    header.code = 0;
    header.un.echo.id = id;
    header.un.echo.sequence = seq;
    header.checksum = 0;
    header.checksum = count_checksum((uint16_t *)&header, sizeof(header));

    return header;
}

uint16_t ICMPSender::count_checksum(const uint16_t * hdr, int length)
{
    if((length & 1) == 1)
        throw SocketException("Incorrect length of ICMP header.");

    uint32_t sum = 0;
    const uint16_t * ptr = hdr;

    for(int i = 0; i < length; i += 2)
    {
        sum += *ptr;
        ++ptr;
    }

    sum = (sum >> 16) + (sum & 0xFFFF);

    return (uint16_t)(~(sum + (sum >> 16)));
}
