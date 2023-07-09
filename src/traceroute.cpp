#include <cstring>
#include <algorithm>
#include <iostream>
#include <set>
#include <string>
#include <unistd.h>
#include "ICMPController.hpp"
#include "Parameters.hpp"

int main(int argc, char * argv[])
{
    RawSocket socket = RawSocket(IPPROTO_ICMP);
    ICMPController socket_ctrl = ICMPController(socket);
    Parameters parameters = ParametersParser().parse(argc, argv);

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
