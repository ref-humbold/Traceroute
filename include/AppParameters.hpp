#ifndef PARAMETERS_HPP_
#define PARAMETERS_HPP_

#include <stdexcept>
#include <string>

struct ParametersException : std::runtime_error
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

    static AppParameters parse(int argc, char * argv[]);

    std::string address;
    size_t steps;

private:
    static constexpr size_t default_steps = 32;
};

#endif
