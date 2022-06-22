/**
 * @file Buffer.test.cpp
 * @author Adrian Szczepanski
 * @date 11-08-2021
 * @brief 
 * @details
 */

#include <libUtils/Buffer.hpp>

#include <CppUTest/CommandLineTestRunner.h>

using namespace Utils;

static constexpr size_t SIZE = 5;

using TestBuffer = Buffer<byte>;

TEST_GROUP(BufferTest)
{
};

TEST(BufferTest, Empty)
{
    TestBuffer buffer(SIZE);

    CHECK_EQUAL(0, buffer.Count());
    CHECK_EQUAL(SIZE, buffer.Capacity());
    CHECK(buffer.IsEmpty());
    CHECK_FALSE(buffer.IsNotEmpty());
    CHECK_FALSE(buffer.IsFull());
}

TEST(BufferTest, Add_OneItem)
{
    TestBuffer buffer(SIZE);
    byte item = 5;

    CHECK(buffer.Add(item));

    CHECK_EQUAL(1, buffer.Count());
    CHECK_FALSE(buffer.IsEmpty());
    CHECK(buffer.IsNotEmpty());
    CHECK_FALSE(buffer.IsFull());
    CHECK(buffer.Data(0) != nullptr);
    CHECK_EQUAL(item, buffer[0]);
}

TEST(BufferTest, Add_Span)
{
    TestBuffer buffer(SIZE);
    byte items[] = { 5, 10, 15, 20 };

    CHECK(buffer.Add({ items, sizeof(items) }));

    CHECK_EQUAL(sizeof(items), buffer.Count());
    CHECK_FALSE(buffer.IsEmpty());
    CHECK(buffer.IsNotEmpty());
    CHECK_FALSE(buffer.IsFull());
}

TEST(BufferTest, Add_Pointer)
{
    TestBuffer buffer(SIZE);
    byte items[] = { 5, 10, 15, 20 };

    CHECK(buffer.Add(items, sizeof(items)));

    CHECK_EQUAL(sizeof(items), buffer.Count());
    CHECK_FALSE(buffer.IsEmpty());
    CHECK(buffer.IsNotEmpty());
    CHECK_FALSE(buffer.IsFull());
}

TEST(BufferTest, Add_MoreThanCount)
{
    TestBuffer buffer(SIZE);
    byte items[] = { 5, 10, 15, 20, 25, 30 };

    CHECK_FALSE(buffer.Add(items, sizeof(items)));
    CHECK(buffer.IsEmpty());

    CHECK(buffer.Add(items, sizeof(items) - 1));

    CHECK_EQUAL(sizeof(items) - 1, buffer.Count());
    CHECK(buffer.IsFull());
}

TEST(BufferTest, Insert_OneItem)
{
    TestBuffer buffer(SIZE);
    byte items[] = { 5, 15 };
    byte inserted = 10;

    buffer.Add(items, 2);
    CHECK(buffer.Insert(1, inserted));

    CHECK_EQUAL(3, buffer.Count());
    CHECK_EQUAL(5, buffer[0]);
    CHECK_EQUAL(10, buffer[1]);
    CHECK_EQUAL(15, buffer[2]);
}

TEST(BufferTest, Insert_OneItem_IndexOutOfBounds)
{
    TestBuffer buffer(SIZE);
    byte items[] = { 5, 15 };
    byte inserted = 10;

    buffer.Add(items, 2);
    CHECK_FALSE(buffer.Insert(2, inserted));

    CHECK_EQUAL(2, buffer.Count());
}

TEST(BufferTest, Insert_Span)
{
    TestBuffer buffer(SIZE);
    byte items[] = { 5, 15 };
    byte inserted[] = { 1, 2, 3 };

    buffer.Add(items, 2);
    CHECK(buffer.Insert(1, { inserted, 3 }));

    CHECK_EQUAL(5, buffer.Count());
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

    buffer.Add(items, 2);
    CHECK_FALSE(buffer.Insert(1, { inserted, 4 }));

    CHECK_EQUAL(2, buffer.Count());
}

TEST(BufferTest, Shrink)
{
    TestBuffer buffer(SIZE);
    byte items[] = { 5, 15 };

    buffer.Add(items, 2);
    CHECK_FALSE(buffer.Shrink(3));
    CHECK(buffer.Shrink(2));
    CHECK(buffer.IsEmpty());
}

TEST(BufferTest, ShiftLeft)
{
    TestBuffer buffer(SIZE);
    byte items[] = { 5, 10, 15, 20, 25 };

    buffer.Add(items, 5);
    CHECK_FALSE(buffer.ShiftLeft(1, 5));
    CHECK(buffer.ShiftLeft(1, 3));

    CHECK_EQUAL(2, buffer.Count());
    CHECK_EQUAL(5, buffer[0]);
    CHECK_EQUAL(25, buffer[1]);
}