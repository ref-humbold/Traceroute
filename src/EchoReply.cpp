#include "EchoReply.hpp"

void EchoReply::add(Ip4Address addr, size_t time_ms)
{
    address_times.emplace(addr, std::vector<size_t>());
    address_times[addr].emplace_back(time_ms);
    ++received_count;
    average_time += (time_ms - average_time) / received_count;
}

std::ostream & operator<<(std::ostream & os, const EchoReply & reply)
{
    if(reply.address_times.empty())
    {
        os << "*";
        return os;
    }

    std::string address_separator = "";

    for(auto && addr_time : reply.address_times)
    {
        std::string time_separator = "";

        os << address_separator << addr_time.first << " -- ";

        for(auto && resp_time : addr_time.second)
        {
            os << time_separator << resp_time << " ms";
            time_separator = ", ";
        }

        address_separator = " / ";
    }

    os << " (avg " << reply.average_time << " ms)";
    return os;
}
