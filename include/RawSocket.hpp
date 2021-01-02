#ifndef RAW_SOCKET_HPP_
#define RAW_SOCKET_HPP_

#include <cerrno>
#include <cstdlib>
#include <cstring>
#include <exception>
#include <stdexcept>
#include <string>
#include <unistd.h>

struct SocketException : public std::logic_error
{
    explicit SocketException(const char * s) : std::logic_error(s)
    {
    }

    explicit SocketException(const std::string & s) : std::logic_error(s)
    {
    }
};

class RawSocket
{
public:
    explicit RawSocket(int protocol) : descriptor_{socket(AF_INET, SOCK_RAW, protocol)}
    {
        if(descriptor_ < 0)
            throw SocketException(strerror(errno));
    }

    ~RawSocket()
    {
        close(descriptor_);
    }

    RawSocket(const RawSocket &) = delete;
    RawSocket(RawSocket &&) = default;
    RawSocket & operator=(const RawSocket &) = delete;
    RawSocket & operator=(RawSocket &&) = default;

    int descriptor() const
    {
        return descriptor_;
    }

private:
    int descriptor_;
};

#endif
