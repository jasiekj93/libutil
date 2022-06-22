/**
 * @file StaticList.test.cpp
 * @author Adrian Szczepanski
 * @date 11-08-2021
 * @brief 
 * @details
 */

#include <libUtils/Static/List.hpp>

#include <CppUTest/CommandLineTestRunner.h>

using namespace Utils;

static constexpr size_t SIZE = 5;
using TestList = Static::List<int, SIZE>;


TEST_GROUP(StaticListTest)
{
};

TEST(StaticListTest, Empty)
{
    TestList list;

    CHECK_EQUAL(SIZE, list.Size());
    CHECK_EQUAL(0, list.Count());
    CHECK(list.IsEmpty());
    CHECK_FALSE(list.IsNotEmpty());
    CHECK_FALSE(list.IsFull());
}

TEST(StaticListTest, PushBack_OneItem)
{
    TestList list;
    int value = 5;

    CHECK(list.PushBack(value));

    CHECK_EQUAL(1, list.Count());
    CHECK_FALSE(list.IsEmpty());
    CHECK(list.IsNotEmpty());
    CHECK_FALSE(list.IsFull());
    CHECK_EQUAL(value, *list[0]);
    CHECK(nullptr == list[1]);
}

TEST(StaticListTest, PushBack_TwoItems)
{
    TestList list;
    int value1 = 5;
    int value2 = 10;

    CHECK(list.PushBack(value1));
    CHECK(list.PushBack(value2));

    CHECK_EQUAL(2, list.Count());
    CHECK_FALSE(list.IsEmpty());
    CHECK(list.IsNotEmpty());
    CHECK_FALSE(list.IsFull());
    CHECK_EQUAL(value1, *list[0]);
    CHECK_EQUAL(value2, *list[1]);
    CHECK(nullptr == list[2]);
}

TEST(StaticListTest, PushBack_MoreThanCount)
{
    TestList list;
    int value = 5;

    for(size_t i = 0; i < SIZE; i++)
        CHECK(list.PushBack(value++));
    
    CHECK_FALSE(list.PushBack(value));

    CHECK_EQUAL(SIZE, list.Count());
    CHECK_FALSE(list.IsEmpty());
    CHECK(list.IsNotEmpty());
    CHECK(list.IsFull());
}

TEST(StaticListTest, PushFront_OneItem)
{
    TestList list;
    int value = 5;

    CHECK(list.PushFront(value));

    CHECK_EQUAL(1, list.Count());
    CHECK_FALSE(list.IsEmpty());
    CHECK(list.IsNotEmpty());
    CHECK_FALSE(list.IsFull());
    CHECK_EQUAL(value, *list[0]);
    CHECK(nullptr == list[1]);
}

TEST(StaticListTest, PushFront_TwoItems)
{
    TestList list;
    int value1 = 5;
    int value2 = 10;

    CHECK(list.PushFront(value1));
    CHECK(list.PushFront(value2));

    CHECK_EQUAL(2, list.Count());
    CHECK_FALSE(list.IsEmpty());
    CHECK(list.IsNotEmpty());
    CHECK_FALSE(list.IsFull());
    CHECK_EQUAL(value2, *list[0]);
    CHECK_EQUAL(value1, *list[1]);
    CHECK(nullptr == list[2]);
}

TEST(StaticListTest, PushFront_MoreThanCount)
{
    TestList list;
    int value = 5;

    for(size_t i = 0; i < SIZE; i++)
        CHECK(list.PushFront(value++));
    
    CHECK_FALSE(list.PushFront(value));

    CHECK_EQUAL(SIZE, list.Count());
    CHECK_FALSE(list.IsEmpty());
    CHECK(list.IsNotEmpty());
    CHECK(list.IsFull());
}

TEST(StaticListTest, PopBack_OneItem)
{
    TestList list;
    int value = 5;

    list.PushBack(value);

    CHECK(list.PopBack());
    CHECK_FALSE(list.PopBack());

    CHECK_EQUAL(0, list.Count());
    CHECK(list.IsEmpty());
    CHECK(nullptr == list[0]);
}

TEST(StaticListTest, PopBack_AndPush)
{
    TestList list;
    int value = 5;

    list.PushBack(value);
    CHECK(list.PopBack());
    CHECK(list.PushBack(value+1));

    CHECK_EQUAL(1, list.Count());
    CHECK_EQUAL((value + 1), *list[0]);
}

TEST(StaticListTest, PopFront_OneItem)
{
    TestList list;
    int value = 5;

    list.PushBack(value);

    CHECK(list.PopFront());
    CHECK_FALSE(list.PopFront());

    CHECK_EQUAL(0, list.Count());
    CHECK(list.IsEmpty());
    CHECK(nullptr == list[0]);
}

TEST(StaticListTest, PopFront_AndPush)
{
    TestList list;
    int value = 5;

    list.PushBack(value);
    CHECK(list.PopFront());
    CHECK(list.PushBack(value+1));

    CHECK_EQUAL(1, list.Count());
    CHECK_EQUAL((value + 1), *list[0]);
}