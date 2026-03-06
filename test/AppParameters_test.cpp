#include <gtest/gtest.h>
#include "AppParameters.hpp"

char program[] = "traceroute";
char limit_flag[] = "-L";

TEST(AppParametersTest, parse_WhenAddressOnly_ThenParsedWithDefaultSteps)
{
    // given
    std::string address = "127.0.0.1";
    char * argv[] = { &program[0], &address[0], nullptr };
    int argc = sizeof(argv) / sizeof(char*) - 1;

    // when
    AppParameters result = AppParameters::parse(argc, argv);

    // then
    EXPECT_EQ(32, result.steps);
    EXPECT_EQ(address, result.address);
}

TEST(AppParametersTest, parse_WhenLimitValue_ThenParsed)
{
    // given
    std::string address = "127.0.0.1";
    std::string limit = "20";
    char * argv[] = { &program[0], &limit_flag[0], &limit[0], &address[0], nullptr };
    int argc = sizeof(argv) / sizeof(char*) - 1;

    // when
    AppParameters result = AppParameters::parse(argc, argv);

    // then
    EXPECT_EQ(std::stoul(limit), result.steps);
    EXPECT_EQ(address, result.address);
}

TEST(AppParametersTest, parse_WhenMissingLimitValue_ThenParametersException)
{
    // given
    std::string address = "127.0.0.1";
    char * argv[] = { &program[0], &limit_flag[0], &address[0], nullptr };
    int argc = sizeof(argv) / sizeof(char*) - 1;

    // when
    auto exec = [&]() { AppParameters::parse(argc, argv); };

    // then
    EXPECT_THROW(exec(), ParametersException);
}

TEST(AppParametersTest, parse_WhenMissingAddress_ThenParametersException)
{
    // given
    char * argv[] = { &program[0], nullptr };
    int argc = sizeof(argv) / sizeof(char*) - 1;

    // when
    auto exec = [&]() { AppParameters::parse(argc, argv); };

    // then
    EXPECT_THROW(exec(), ParametersException);
}

TEST(AppParametersTest, parse_WhenMissingLimitValueAndAddress_ThenParametersException)
{
    // given
    char * argv[] = { &program[0], &limit_flag[0], nullptr };
    int argc = sizeof(argv) / sizeof(char*) - 1;

    // when
    auto exec = [&]() { AppParameters::parse(argc, argv); };

    // then
    EXPECT_THROW(exec(), ParametersException);
}

TEST(AppParametersTest, parse_WhenLimitValueAndMissingAddress_ThenParametersException)
{
    // given
    std::string limit = "20";
    char * argv[] = { &program[0], &limit_flag[0], &limit[0], nullptr };
    int argc = sizeof(argv) / sizeof(char*) - 1;

    // when
    auto exec = [&]() { AppParameters::parse(argc, argv); };

    // then
    EXPECT_THROW(exec(), ParametersException);
}
