/**
 * @file Queue.test.cpp
 * @author Adrian Szczepanski
 * @date 11-08-2021
 * @brief 
 * @details
 */

#include <libutil/Queue.hpp>
#include <libutil/DataUnit.hpp>

#include <CppUTest/CommandLineTestRunner.h>

using namespace util;

static constexpr size_t SIZE = 5;

using TestQueue = Queue<byte>;

TEST_GROUP(QueueTest)
{
};

TEST(QueueTest, Empty)
{
    TestQueue queue(SIZE);

    CHECK_EQUAL(0, queue.count());
    CHECK_EQUAL(SIZE, queue.size());
    CHECK(queue.isEmpty());
    CHECK_FALSE(queue.isNotEmpty());
    CHECK_FALSE(queue.isFull());
}