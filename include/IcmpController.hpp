#ifndef ICMP_CONTROLLER_HPP_
#define ICMP_CONTROLLER_HPP_

#include <optional>
#include "RepliesMap.hpp"
#include "SocketReceiver.hpp"
#include "SocketSender.hpp"

class IcmpController
{
public:
    explicit IcmpController(const RawSocket & s)
        : socket{s}, sender{SocketSender(s)}, receiver{SocketReceiver(s)}
    {
    }

    void echo_request(const Ip4Address & address, uint16_t id, uint16_t ttl);
    RepliesMap echo_reply(uint16_t id, uint16_t ttl);

    const uint16_t attempts = 3;

private:
    std::optional<Ip4Address> receive_echo(uint16_t id, uint16_t ttl);
    uint16_t count_checksum(const uint16_t * header, size_t length);
    icmphdr prepare_icmp(uint16_t id, uint16_t seq);
    std::tuple<const iphdr *, const icmphdr *, const uint8_t *> extract_headers(
            const uint8_t * ptr);

    const RawSocket & socket;
    SocketSender sender;
    SocketReceiver receiver;
};

#endif
