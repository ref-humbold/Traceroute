#include <cstring>
#include <algorithm>
#include <iostream>
#include <set>
#include <string>
#include <unistd.h>
#include "ICMPController.hpp"

void print_results(uint16_t ttl, const EchoReply & reply)
{
    std::cout << (ttl < 10 ? " " : "") << static_cast<size_t>(ttl) << ". " << reply << "\n";
}

int main(int argc, char * argv[])
{
    RawSocket socket = RawSocket(IPPROTO_ICMP);
    ICMPController socket_ctrl = ICMPController(socket);

    if(argc < 2)
    {
        std::cerr << "No destination IP specified.";
        return 1;
    }

    IPAddress addr(argv[1]);
    uint16_t pid = getpid();
    int steps = 30;

    std::cout << "  traceroute :: destination " << addr << " :: max " << steps << " steps\n";

    for(int i = 1; i <= steps; ++i)
    {
        socket_ctrl.echo_request(addr, pid, i);

        EchoReply reply = socket_ctrl.echo_reply(pid, i);

        print_results(i, reply);

        if(std::any_of(reply.addresses.begin(), reply.addresses.end(),
                       [addr](const IPAddress & a) { return a == addr; }))
            break;
    }

    return 0;
}
