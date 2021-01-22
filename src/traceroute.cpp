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

    IPAddress destination(argv[1]);
    uint16_t pid = getpid();
    size_t steps = 32;

    std::cout << "  traceroute :: destination " << destination << " :: max " << steps << " steps\n";

    for(size_t i = 1; i <= steps; ++i)
    {
        socket_ctrl.echo_request(destination, pid, i);

        EchoReply reply = socket_ctrl.echo_reply(pid, i);

        std::cout << (i < 10 ? " " : "") << i << ". " << reply << "\n";

        if(reply.address_times.find(destination) != reply.address_times.end())
            break;
    }

    return 0;
}
