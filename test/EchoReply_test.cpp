#include <gtest/gtest.h>
#include "EchoReply.hpp"

constexpr double offset = 1e-6;

TEST(EchoReplyTest, add_WhenFirstReceived_ThenAdded)
{
    // given
    EchoReply reply;
    Ip4Address address("127.0.0.1");
    size_t time_ms = 30;

    // when
    reply.add(address, time_ms);

    // then
    EXPECT_EQ(1, reply.address_times.size());
    EXPECT_EQ(std::vector<size_t>({time_ms}), reply.address_times.at(address));
    EXPECT_EQ(1, reply.received_count);
    EXPECT_NEAR(time_ms, reply.average_time, offset);
}

TEST(EchoReplyTest, add_WhenReceivedFromSameAddress_ThenAddedToAddress)
{
    // given
    EchoReply reply;
    Ip4Address address("127.0.0.1");
    size_t time_ms_1 = 30, time_ms_2 = 20;

    reply.add(address, time_ms_1);

    // when
    reply.add(address, time_ms_2);

    // then
    EXPECT_EQ(1, reply.address_times.size());
    EXPECT_EQ(std::vector<size_t>({time_ms_1, time_ms_2}), reply.address_times.at(address));
    EXPECT_EQ(2, reply.received_count);
    EXPECT_NEAR((time_ms_1 + time_ms_2) / 2, reply.average_time, offset);
}

TEST(EchoReplyTest, add_WhenReceivedFromOtherAddress_ThenAddedAsOther)
{
    // given
    EchoReply reply;
    Ip4Address address_1("127.0.0.1"), address_2("127.0.0.2");
    size_t time_ms_1 = 30, time_ms_2 = 20;

    reply.add(address_1, time_ms_1);

    // when
    reply.add(address_2, time_ms_2);

    // then
    EXPECT_EQ(2, reply.address_times.size());
    EXPECT_EQ(std::vector<size_t>({time_ms_1}), reply.address_times.at(address_1));
    EXPECT_EQ(std::vector<size_t>({time_ms_2}), reply.address_times.at(address_2));
    EXPECT_EQ(2, reply.received_count);
    EXPECT_NEAR((time_ms_1 + time_ms_2) / 2, reply.average_time, offset);
}
