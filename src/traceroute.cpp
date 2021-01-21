#include <cstring>
#include <algorithm>
#include <iostream>
#include <set>
#include <string>
#include <unistd.h>
#include "ICMPController.hpp"

int main(int argc, char * argv[])
{
    RawSocket socket = RawSocket(IPPROTO_ICMP);
    ICMPController socket_ctrl = ICMPController(socket);

    if(argc < 2)
    {
        std::cerr << "No destination IP specified";
        return 1;
    }

    IPAddress address(argv[1]);
    uint16_t pid = getpid();
    size_t steps = 30;

    std::cout << "  traceroute :: destination " << address << " :: max " << steps << " steps\n";

    for(size_t i = 1; i <= steps; ++i)
    {
        socket_ctrl.echo_request(address, pid, i);

        EchoReply reply = socket_ctrl.echo_reply(pid, i);

        std::cout << (i < 10 ? " " : "") << i << ". " << reply << "\n";

        if(reply.address_times.find(address) != reply.address_times.end())
            break;
    }

    return 0;
}
