#include <cstdlib>
#include <cstring>
#include <iostream>
#include <algorithm>
#include <set>
#include <string>
#include <unistd.h>
#include "ICMPController.hpp"
#include "IPAddress.hpp"
#include "RawSocket.hpp"

void print_results(uint16_t ttl, const std::set<IPAddress> & recvaddr, int avg_time)
{
    std::cout << static_cast<unsigned int>(ttl) << ". ";

    if(avg_time < 0)
    {
        if(recvaddr.size() == 0)
            std::cout << "*\n";
        else
        {
            for(auto addr : recvaddr)
                std::cout << addr << " ";

            std::cout << "???\n";
        }
    }
    else
    {
        for(auto addr : recvaddr)
            std::cout << addr << " ";

        std::cout << avg_time / 1000 << "ms\n";
    }
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

    for(int i = 1; i <= 30; ++i)
    {
        std::set<IPAddress> recvaddr;
        int avg_time;

        socket_ctrl.echo_request(addr, pid, i);
        std::tie(recvaddr, avg_time) = socket_ctrl.echo_reply(pid, i);
        print_results(i, recvaddr, avg_time);

        if(std::any_of(recvaddr.begin(), recvaddr.end(),
                       [addr](const IPAddress & a) { return a == addr; }))
            break;
    }

    return 0;
}
