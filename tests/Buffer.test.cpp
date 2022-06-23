/**
 * @file Buffer.test.cpp
 * @author Adrian Szczepanski
 * @date 11-08-2021
 * @brief 
 * @details
 */

#include <libutil/Buffer.hpp>
#include <libutil/DataUnit.hpp>

#include <CppUTest/CommandLineTestRunner.h>

using namespace util;

static constexpr size_t SIZE = 5;

using TestBuffer = Buffer<byte>;

TEST_GROUP(BufferTest)
{
};

TEST(BufferTest, Empty)
{
    TestBuffer buffer(SIZE);

    CHECK_EQUAL(0, buffer.count());
    CHECK_EQUAL(SIZE, buffer.capacity());
    CHECK(buffer.isEmpty());
    CHECK_FALSE(buffer.isNotEmpty());
    CHECK_FALSE(buffer.isFull());
}

TEST(BufferTest, Add_OneItem)
{
    TestBuffer buffer(SIZE);
    byte item = 5;

    CHECK(buffer.add(item));

    CHECK_EQUAL(1, buffer.count());
    CHECK_FALSE(buffer.isEmpty());
    CHECK(buffer.isNotEmpty());
    CHECK_FALSE(buffer.isFull());
    CHECK(buffer.data(0) != nullptr);
    CHECK_EQUAL(item, buffer[0]);
}

TEST(BufferTest, Add_Span)
{
    TestBuffer buffer(SIZE);
    byte items[] = { 5, 10, 15, 20 };

    CHECK(buffer.add({ items, sizeof(items) }));

    CHECK_EQUAL(sizeof(items), buffer.count());
    CHECK_FALSE(buffer.isEmpty());
    CHECK(buffer.isNotEmpty());
    CHECK_FALSE(buffer.isFull());
}

TEST(BufferTest, Add_Pointer)
{
    TestBuffer buffer(SIZE);
    byte items[] = { 5, 10, 15, 20 };

    CHECK(buffer.add(items, sizeof(items)));

    CHECK_EQUAL(sizeof(items), buffer.count());
    CHECK_FALSE(buffer.isEmpty());
    CHECK(buffer.isNotEmpty());
    CHECK_FALSE(buffer.isFull());
}

TEST(BufferTest, Add_MoreThanCount)
{
    TestBuffer buffer(SIZE);
    byte items[] = { 5, 10, 15, 20, 25, 30 };

    CHECK_FALSE(buffer.add(items, sizeof(items)));
    CHECK(buffer.isEmpty());

    CHECK(buffer.add(items, sizeof(items) - 1));

    CHECK_EQUAL(sizeof(items) - 1, buffer.count());
    CHECK(buffer.isFull());
}

TEST(BufferTest, Insert_OneItem)
{
    TestBuffer buffer(SIZE);
    byte items[] = { 5, 15 };
    byte inserted = 10;

    buffer.add(items, 2);
    CHECK(buffer.insert(1, inserted));

    CHECK_EQUAL(3, buffer.count());
    CHECK_EQUAL(5, buffer[0]);
    CHECK_EQUAL(10, buffer[1]);
    CHECK_EQUAL(15, buffer[2]);
}

TEST(BufferTest, Insert_OneItem_IndexOutOfBounds)
{
    TestBuffer buffer(SIZE);
    byte items[] = { 5, 15 };
    byte inserted = 10;

    buffer.add(items, 2);
    CHECK_FALSE(buffer.insert(2, inserted));

    CHECK_EQUAL(2, buffer.count());
}

TEST(BufferTest, Insert_Span)
{
    TestBuffer buffer(SIZE);
    byte items[] = { 5, 15 };
    byte inserted[] = { 1, 2, 3 };

    buffer.add(items, 2);
    CHECK(buffer.insert(1, { inserted, 3 }));

    CHECK_EQUAL(5, buffer.count());
    CHECK_EQUAL(5, buffer[0]);
    CHECK_EQUAL(1, buffer[1]);
    CHECK_EQUAL(2, buffer[2]);
    CHECK_EQUAL(3, buffer[3]);
    CHECK_EQUAL(15, buffer[4]);
}

TEST(BufferTest, Insert_Span_MoreThanCount)
{
    TestBuffer buffer(SIZE);
    byte items[] = { 5, 15 };
    byte inserted[] = { 1, 2, 3, 4 };

    buffer.add(items, 2);
    CHECK_FALSE(buffer.insert(1, { inserted, 4 }));

    CHECK_EQUAL(2, buffer.count());
}

TEST(BufferTest, Shrink)
{
    TestBuffer buffer(SIZE);
    byte items[] = { 5, 15 };

    buffer.add(items, 2);
    CHECK_FALSE(buffer.shrink(3));
    CHECK(buffer.shrink(2));
    CHECK(buffer.isEmpty());
}

TEST(BufferTest, ShiftLeft)
{
    TestBuffer buffer(SIZE);
    byte items[] = { 5, 10, 15, 20, 25 };

    buffer.add(items, 5);
    CHECK_FALSE(buffer.shiftLeft(1, 5));
    CHECK(buffer.shiftLeft(1, 3));

    CHECK_EQUAL(2, buffer.count());
    CHECK_EQUAL(5, buffer[0]);
    CHECK_EQUAL(25, buffer[1]);
}

TEST(BufferTest, SBuffer_Test)
{
    SBuffer<byte, SIZE> buffer;
    byte items[] = { 5, 15 };
    byte inserted = 10;

    buffer.add(items, 2);
    CHECK(buffer.insert(1, inserted));

    CHECK_EQUAL(3, buffer.count());
    CHECK_EQUAL(5, buffer[0]);
    CHECK_EQUAL(10, buffer[1]);
    CHECK_EQUAL(15, buffer[2]);
}