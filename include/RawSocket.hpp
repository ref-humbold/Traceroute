#ifndef _RAW_SOCKET_HPP_
#define _RAW_SOCKET_HPP_

#include <cstdlib>
#include <cerrno>
#include <cstring>
#include <exception>
#include <stdexcept>
#include <arpa/inet.h>
#include <netinet/ip.h>
#include <unistd.h>

class SocketException : public std::logic_error
{
public:
    explicit SocketException(const char * s) : std::logic_error(s)
    {
    }
};

class RawSocket
{
public:
    explicit RawSocket(int protocol) : descr{socket(AF_INET, SOCK_RAW, protocol)}
    {
        if(descr < 0)
            throw SocketException(strerror(errno));
    }

    ~RawSocket()
    {
        close(descr);
    }

    RawSocket(const RawSocket & raw_sck) = delete;
    RawSocket(RawSocket && raw_sck) = default;
    RawSocket & operator=(const RawSocket & raw_sck) = delete;
    RawSocket & operator=(RawSocket && raw_sck) = default;

    int descriptor() const
    {
        return descr;
    }

private:
    int descr;
};

#endif
