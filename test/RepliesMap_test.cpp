#include <gtest/gtest.h>
#include "RepliesMap.hpp"

constexpr double offset = 1e-6;

TEST(RepliesMapTest, add_WhenFirstReceived_ThenAdded)
{
    // given
    RepliesMap replies_map;
    Ip4Address address(0x7F000001);
    size_t time_ms = 30;

    // when
    replies_map.add(address, time_ms);

    // then
    EXPECT_EQ(std::vector<size_t>({time_ms}), replies_map.at(address));
    EXPECT_EQ(1, replies_map.size());
    EXPECT_NEAR(time_ms, replies_map.average_time(), offset);
}

TEST(RepliesMapTest, add_WhenReceivedFromSameAddress_ThenAddedToAddress)
{
    // given
    RepliesMap replies_map;
    Ip4Address address(0x7F000001);
    size_t time_ms_1 = 30, time_ms_2 = 20;

    replies_map.add(address, time_ms_1);

    // when
    replies_map.add(address, time_ms_2);

    // then
    EXPECT_EQ(std::vector<size_t>({time_ms_1, time_ms_2}), replies_map.at(address));
    EXPECT_EQ(2, replies_map.size());
    EXPECT_NEAR((time_ms_1 + time_ms_2) / 2, replies_map.average_time(), offset);
}

TEST(RepliesMapTest, add_WhenReceivedFromOtherAddress_ThenAddedAsOther)
{
    // given
    RepliesMap replies_map;
    Ip4Address address_1(0x7F000001), address_2(0x7F000002);
    size_t time_ms_1 = 30, time_ms_2 = 20;

    replies_map.add(address_1, time_ms_1);

    // when
    replies_map.add(address_2, time_ms_2);

    // then
    EXPECT_EQ(std::vector<size_t>({time_ms_1}), replies_map.at(address_1));
    EXPECT_EQ(std::vector<size_t>({time_ms_2}), replies_map.at(address_2));
    EXPECT_EQ(2, replies_map.size());
    EXPECT_NEAR((time_ms_1 + time_ms_2) / 2, replies_map.average_time(), offset);
}

TEST(RepliesMapTest, operatorLeftShift_WhenEmpty_ThenSingleAsterisk)
{
    // given
    RepliesMap replies_map;

    // when
    std::ostringstream result;

    result << replies_map;

    // then
    EXPECT_EQ("*", result.str());
}

TEST(RepliesMapTest, operatorLeftShift_WhenSingleAddress_ThenAllTogether)
{
    // given
    RepliesMap replies_map;

    replies_map.add(Ip4Address(0x7F000001), 10);
    replies_map.add(Ip4Address(0x7F000001), 20);
    replies_map.add(Ip4Address(0x7F000001), 30);

    // when
    std::ostringstream result;

    result << replies_map;

    // then
    EXPECT_EQ("127.0.0.1 -- 10 ms, 20 ms, 30 ms (avg 20 ms)", result.str());
}

TEST(RepliesMapTest, operatorLeftShift_WhenMultipleAddresses_ThenSeparated)
{
    // given
    RepliesMap replies_map;

    replies_map.add(Ip4Address(0x7F000001), 10);
    replies_map.add(Ip4Address(0x7F000002), 20);
    replies_map.add(Ip4Address(0x7F000001), 30);
    replies_map.add(Ip4Address(0x7F000002), 40);
    replies_map.add(Ip4Address(0x7F000003), 50);

    // when
    std::ostringstream result;

    result << replies_map;

    // then
    EXPECT_EQ(
            "127.0.0.1 -- 10 ms, 30 ms / 127.0.0.2 -- 20 ms, 40 ms / 127.0.0.3 -- 50 ms (avg 30 ms)",
            result.str());
}
