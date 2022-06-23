/**
 * @file List.test.cpp
 * @author Adrian Szczepanski
 * @date 11-08-2021
 * @brief 
 * @details
 */

#include <libutil/List.hpp>

#include <CppUTest/CommandLineTestRunner.h>

using namespace util;

static constexpr size_t SIZE = 5;
using TestList = SList<int, SIZE>;


TEST_GROUP(ListTest)
{
};

TEST(ListTest, Empty)
{
    TestList list;

    CHECK_EQUAL(SIZE, list.size());
    CHECK_EQUAL(0, list.count());
    CHECK(list.isEmpty());
    CHECK_FALSE(list.isNotEmpty());
    CHECK_FALSE(list.isFull());
}

TEST(ListTest, PushBack_OneItem)
{
    TestList list;
    int value = 5;

    CHECK(list.pushBack(value));

    CHECK_EQUAL(1, list.count());
    CHECK_FALSE(list.isEmpty());
    CHECK(list.isNotEmpty());
    CHECK_FALSE(list.isFull());
    CHECK_EQUAL(value, *list[0]);
    CHECK(nullptr == list[1]);
}

TEST(ListTest, PushBack_TwoItems)
{
    TestList list;
    int value1 = 5;
    int value2 = 10;

    CHECK(list.pushBack(value1));
    CHECK(list.pushBack(value2));

    CHECK_EQUAL(2, list.count());
    CHECK_FALSE(list.isEmpty());
    CHECK(list.isNotEmpty());
    CHECK_FALSE(list.isFull());
    CHECK_EQUAL(value1, *list[0]);
    CHECK_EQUAL(value2, *list[1]);
    CHECK(nullptr == list[2]);
}

TEST(ListTest, PushBack_MoreThanCount)
{
    TestList list;
    int value = 5;

    for(size_t i = 0; i < SIZE; i++)
        CHECK(list.pushBack(value++));
    
    CHECK_FALSE(list.pushBack(value));

    CHECK_EQUAL(SIZE, list.count());
    CHECK_FALSE(list.isEmpty());
    CHECK(list.isNotEmpty());
    CHECK(list.isFull());
}

TEST(ListTest, PushFront_OneItem)
{
    TestList list;
    int value = 5;

    CHECK(list.pushFront(value));

    CHECK_EQUAL(1, list.count());
    CHECK_FALSE(list.isEmpty());
    CHECK(list.isNotEmpty());
    CHECK_FALSE(list.isFull());
    CHECK_EQUAL(value, *list[0]);
    CHECK(nullptr == list[1]);
}

TEST(ListTest, PushFront_TwoItems)
{
    TestList list;
    int value1 = 5;
    int value2 = 10;

    CHECK(list.pushFront(value1));
    CHECK(list.pushFront(value2));

    CHECK_EQUAL(2, list.count());
    CHECK_FALSE(list.isEmpty());
    CHECK(list.isNotEmpty());
    CHECK_FALSE(list.isFull());
    CHECK_EQUAL(value2, *list[0]);
    CHECK_EQUAL(value1, *list[1]);
    CHECK(nullptr == list[2]);
}

TEST(ListTest, PushFront_MoreThanCount)
{
    TestList list;
    int value = 5;

    for(size_t i = 0; i < SIZE; i++)
        CHECK(list.pushFront(value++));
  
    CHECK_FALSE(list.pushFront(value));

    CHECK_EQUAL(SIZE, list.count());
    CHECK_FALSE(list.isEmpty());
    CHECK(list.isNotEmpty());
    CHECK(list.isFull());
}

TEST(ListTest, PopBack_OneItem)
{
    TestList list;
    int value = 5;

    list.pushBack(value);

    CHECK(list.popBack());
    CHECK_FALSE(list.popBack());

    CHECK_EQUAL(0, list.count());
    CHECK(list.isEmpty());
    CHECK(nullptr == list[0]);
}

TEST(ListTest, PopBack_AndPush)
{
    TestList list;
    int value = 5;

    list.pushBack(value);
    CHECK(list.popBack());
    CHECK(list.pushBack(value+1));

    CHECK_EQUAL(1, list.count());
    CHECK_EQUAL((value + 1), *list[0]);
}

TEST(ListTest, PopFront_OneItem)
{
    TestList list;
    int value = 5;

    list.pushBack(value);

    CHECK(list.popFront());
    CHECK_FALSE(list.popFront());

    CHECK_EQUAL(0, list.count());
    CHECK(list.isEmpty());
    CHECK(nullptr == list[0]);
}

TEST(ListTest, PopFront_AndPush)
{
    TestList list;
    int value = 5;

    list.pushBack(value);
    CHECK(list.popFront());
    CHECK(list.pushBack(value+1));

    CHECK_EQUAL(1, list.count());
    CHECK_EQUAL((value + 1), *list[0]);
}