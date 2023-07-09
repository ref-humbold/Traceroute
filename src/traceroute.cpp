#include <cstring>
#include <algorithm>
#include <iostream>
#include <set>
#include <string>
#include <unistd.h>
#include "AppParameters.hpp"
#include "ICMPController.hpp"

int main(int argc, char * argv[])
try
{
    RawSocket socket = RawSocket(IPPROTO_ICMP);
    ICMPController socket_ctrl = ICMPController(socket);
    AppParameters parameters = parse_args(argc, argv);

    IPv4Address destination(parameters.address);
    uint16_t pid = getpid();

    std::cout << "  traceroute :: destination " << destination << " :: max " << parameters.steps
              << " steps\n";

    for(size_t i = 1; i <= parameters.steps; ++i)
    {
        socket_ctrl.echo_request(destination, pid, i);

        EchoReply reply = socket_ctrl.echo_reply(pid, i);

        std::cout << (i < 10 ? " " : "") << i << ". " << reply << "\n";

        if(reply.address_times.find(destination) != reply.address_times.end())
            break;
    }

    return 0;
}
catch(const std::exception & ex)
{
    std::cerr << "ERROR: " << ex.what() << "\n";
    return 1;
}
