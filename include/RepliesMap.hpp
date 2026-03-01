#ifndef REPLIES_MAP_HPP
#define REPLIES_MAP_HPP

#include <iostream>
#include <map>
#include <vector>
#include "Ip4Address.hpp"

class RepliesMap
{
public:
    double average_time() const
    {
        return average_time_;
    }

    size_t size() const
    {
        return size_;
    }

    const std::vector<size_t> & at(const Ip4Address & address) const
    {
      return address_times.at(address);
    }

    bool contains(const Ip4Address & address) const
    {
        return address_times.find(address) != address_times.end();
    }

    void add(Ip4Address address, size_t time_ms);

    friend std::ostream & operator<<(std::ostream & os, const RepliesMap & replies_map);

private:
    std::map<Ip4Address, std::vector<size_t>> address_times;
    double average_time_ = 0.0;
    size_t size_ = 0;
};

std::ostream & operator<<(std::ostream & os, const RepliesMap & replies_map);

#endif
