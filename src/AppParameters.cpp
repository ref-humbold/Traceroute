#include "AppParameters.hpp"
#include <unistd.h>

using namespace std::string_literals;

size_t parse_number(const std::string & s, const std::string & arg_name)
{
    size_t pos, value;

    try
    {
        value = std::stoi(s, &pos);
    }
    catch(const std::invalid_argument & e)
    {
        throw ParametersException("Given "s + arg_name + " is not a number"s);
    }

    if(pos < s.length())
        throw ParametersException("Given "s + arg_name + " is not a number"s);

    return value;
}

AppParameters parse_args(int argc, char * argv[])
{
    AppParameters params;
    const std::string optstring = ":s:"s;
    int option = getopt(argc, argv, optstring.c_str());

    opterr = 0;

    while(option != -1)
    {
        switch(option)
        {
            case 's':
                params.steps = parse_number(optarg, "steps count"s);
                break;

            case '?':
                throw ParametersException("Unknown option -"s + static_cast<char>(optopt));

            case ':':
                throw ParametersException("Option -"s + static_cast<char>(optopt)
                                          + " requires a number between 2 and 16"s);

            default:
                break;
        }

        option = getopt(argc, argv, optstring.c_str());
    }

    int index = optind;

    if(index >= argc)
        throw ParametersException("No destination IP specified");

    params.address = argv[index];

    return params;
}
