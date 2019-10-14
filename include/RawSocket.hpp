#ifndef RAW_SOCKET_HPP_
#define RAW_SOCKET_HPP_

#include <cstdlib>
#include <cerrno>
#include <cstring>
#include <exception>
#include <stdexcept>
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

    RawSocket(const RawSocket & r) = delete;
    RawSocket(RawSocket && r) = default;
    RawSocket & operator=(const RawSocket & r) = delete;
    RawSocket & operator=(RawSocket && r) = default;

    int descriptor() const
    {
        return descr;
    }

private:
    int descr;
};

#endif
