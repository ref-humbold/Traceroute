#ifndef ECHO_REPLY_HPP
#define ECHO_REPLY_HPP

#include <cstdlib>
#include <iostream>
#include <map>
#include <vector>
#include "Ip4Address.hpp"

struct EchoReply
{
    EchoReply() : average_time{0.0}, received_count{0}
    {
    }

    void add(Ip4Address addr, size_t time_ms);

    std::map<Ip4Address, std::vector<size_t>> address_times;
    double average_time;
    size_t received_count;
};

std::ostream & operator<<(std::ostream & os, const EchoReply & reply);

#endif
