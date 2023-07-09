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

#pragma region Parameters

struct Parameters
{
public:
    Parameters() : address{""}, steps{32}
    {
    }

    std::string address;
    size_t steps;
};

#pragma endregion
#pragma region ParametersParser

class ParametersParser
{
public:
    ParametersParser()
    {
    }

    const Parameters & parse(int argc, char * argv[]);

private:
    Parameters parameters_;
};

#pragma endregion
#endif
