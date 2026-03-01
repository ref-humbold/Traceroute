#include <gtest/gtest.h>
#include "Ip4Address.hpp"

class Ip4AddressTest_Pairs : public testing::TestWithParam<std::pair<std::string, uint32_t>>
{
};

INSTANTIATE_TEST_SUITE_P(,
        Ip4AddressTest_Pairs,
        testing::Values(std::make_pair("127.0.0.1", 0x7F000001),
                std::make_pair("8.8.8.8", 0x08080808),
                std::make_pair("172.16.0.255", 0xAC1000FF),
                std::make_pair("10.44.144.244", 0x0A2C90F4)));

TEST_P(Ip4AddressTest_Pairs, constructor_WhenNumber_ThenCreated)
{
    // given
    std::pair<std::string, uint32_t> params = GetParam();

    // when
    Ip4Address result(params.second);

    // then
    EXPECT_EQ(Ip4Address(params.first), result);
}

TEST_P(Ip4AddressTest_Pairs, constructor_WhenValidString_ThenCreated)
{
    // given
    std::pair<std::string, uint32_t> params = GetParam();

    // when
    Ip4Address result(params.first);

    // then
    EXPECT_EQ(Ip4Address(params.second), result);
}

TEST_P(Ip4AddressTest_Pairs, operatorUint32T_ThenIPv4Number)
{
    // given
    std::pair<std::string, uint32_t> params = GetParam();
    Ip4Address address(params.first);

    // when
    auto result = static_cast<uint32_t>(address);

    // then
    EXPECT_EQ(params.second, result);
}

TEST_P(Ip4AddressTest_Pairs, operatorString_ThenIPv4String)
{
    // given
    std::pair<std::string, uint32_t> params = GetParam();
    Ip4Address address(params.second);

    // when
    auto result = static_cast<std::string>(address);

    // then
    EXPECT_EQ(params.first, result);
}
