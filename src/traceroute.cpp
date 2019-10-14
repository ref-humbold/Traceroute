#include <cstring>
#include <iostream>
#include <algorithm>
#include <set>
#include <string>
#include <unistd.h>
#include "ICMPController.hpp"

void print_results(uint16_t ttl, const std::set<IPAddress> & recv_addr, size_t avg_time,
                   size_t recv_num)
{
    std::cout << (ttl < 10 ? " " : "") << static_cast<unsigned int>(ttl) << ". ";

    if(recv_addr.empty())
        std::cout << "*\n";
    else
    {
        for(auto addr : recv_addr)
            std::cout << addr << " ";

        std::cout << "-- " << avg_time / 1000 << " ms (" << recv_num << ")\n";
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
    int steps = 30;

    std::cout << "  traceroute :: destination " << addr << " :: max " << steps << " steps\n";

    for(int i = 1; i <= steps; ++i)
    {
        std::set<IPAddress> recv_addr;
        size_t avg_time, recv_num;

        socket_ctrl.echo_request(addr, pid, i);
        std::tie(recv_addr, avg_time, recv_num) = socket_ctrl.echo_reply(pid, i);
        print_results(i, recv_addr, avg_time, recv_num);

        if(std::any_of(recv_addr.begin(), recv_addr.end(),
                       [addr](const IPAddress & a) { return a == addr; }))
            break;
    }

    return 0;
}
