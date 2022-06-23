/**
 * @file MessageQueue.test.cpp
 * @author Adrian Szczepanski
 * @date 11-08-2021
 * @brief 
 * @details
 */

#include <libutil/MessageQueue.hpp>

#include <CppUTest/CommandLineTestRunner.h>

using namespace util;

static constexpr size_t SIZE = 5;

using TestQueue = MessageQueue<byte>;

TEST_GROUP(MessageQueueTest)
{
};

TEST(MessageQueueTest, Empty)
{
    TestQueue queue(SIZE);

    CHECK_EQUAL(0, queue.count());
    CHECK_EQUAL(SIZE, queue.size());
}