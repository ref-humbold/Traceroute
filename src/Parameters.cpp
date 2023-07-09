#include "Parameters.hpp"

#pragma region ParametersParser

const Parameters & ParametersParser::parse(int argc, char * argv[])
{
    if(argc < 2)
        throw ParametersException("No destination IP specified");

    parameters_.address = argv[1];
    return parameters_;
}

#pragma endregion
