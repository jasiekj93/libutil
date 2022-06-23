/**
 * @file MutexQueue.test.cpp
 * @author Adrian Szczepanski
 * @date 11-08-2021
 * @brief 
 * @details
 */

#include <libutil/MutexQueue.hpp>

#include <CppUTest/CommandLineTestRunner.h>

using namespace util;

static constexpr size_t SIZE = 5;

using TestQueue = MutexQueue<byte>;

TEST_GROUP(MutexQueueTest)
{
};

TEST(MutexQueueTest, Empty)
{
    TestQueue queue(SIZE);

    CHECK_EQUAL(0, queue.count());
    CHECK_EQUAL(SIZE, queue.size());
    CHECK(queue.isEmpty());
    CHECK_FALSE(queue.isNotEmpty());
    CHECK_FALSE(queue.isFull());
}