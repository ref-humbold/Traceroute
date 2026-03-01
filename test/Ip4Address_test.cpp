#include <gtest/gtest.h>
#include "Ip4Address.hpp"

TEST(Ip4AddressTest, constructor_WhenNumber_ThenCreated)
{
    // when
    Ip4Address result(0x7F000001);

    // then
    EXPECT_EQ(Ip4Address(0x7F000001), result);
}

TEST(Ip4AddressTest, constructor_WhenValidString_ThenCreated)
{
    // when
    Ip4Address result("127.0.0.1");

    // then
    EXPECT_EQ(Ip4Address(0x7F000001), result);
}

TEST(Ip4AddressTest, operatorUint32T_ThenIPv4Number)
{
    // given
    Ip4Address address(0x7F000001);

    // when
    uint32_t result = static_cast<uint32_t>(address);

    // then
    EXPECT_EQ(0x7F000001, result);
}

TEST(Ip4AddressTest, operatorString_ThenIPv4String)
{
    // given
    Ip4Address address(0x7F000001);

    // when
    std::string result = static_cast<std::string>(address);

    // then
    EXPECT_EQ("127.0.0.1", result);
}
