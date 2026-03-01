#include "RepliesMap.hpp"

void RepliesMap::add(Ip4Address address, size_t time_ms)
{
    address_times.emplace(address, std::vector<size_t>());
    address_times[address].emplace_back(time_ms);
    ++size_;
    average_time_ += (time_ms - average_time_) / size_;
}

std::ostream & operator<<(std::ostream & os, const RepliesMap & replies_map)
{
    if(replies_map.address_times.empty())
    {
        os << "*";
        return os;
    }

    std::string address_separator = "";

    for(auto && entry : replies_map.address_times)
    {
        std::string time_separator = "";

        os << address_separator << entry.first << " -- ";

        for(auto && resp_time : entry.second)
        {
            os << time_separator << resp_time << " ms";
            time_separator = ", ";
        }

        address_separator = " / ";
    }

    os << " (avg " << replies_map.average_time_ << " ms)";
    return os;
}
