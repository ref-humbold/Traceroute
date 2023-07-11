#ifndef PARAMETERS_HPP_
#define PARAMETERS_HPP_

#include <exception>
#include <stdexcept>
#include <string>

struct ParametersException : public std::runtime_error
{
    explicit ParametersException(const char * s) : std::runtime_error(s)
    {
    }

    explicit ParametersException(const std::string & s) : std::runtime_error(s)
    {
    }
};

class AppParameters
{
public:
    AppParameters() : address{""}, steps{default_steps}
    {
    }

    std::string address;
    size_t steps;

private:
    static constexpr size_t default_steps = 32;
};

AppParameters parse_args(int argc, char * argv[]);

#endif
