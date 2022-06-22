/**
 * @file List.test.cpp
 * @author Adrian Szczepanski
 * @date 11-08-2021
 * @brief 
 * @details
 */

#include <libUtils/List.hpp>

#include <CppUTest/CommandLineTestRunner.h>

using namespace Utils;

using TestList = List<int>;

TEST_GROUP(ListTest)
{
};

TEST(ListTest, Empty)
{
    TestList list;

    CHECK_EQUAL(0, list.Size());
    CHECK(list.IsEmpty());
}

TEST(ListTest, PushBack_OneItem)
{
    TestList list;
    int value = 5;

    list.PushBack(value);

    CHECK_EQUAL(1, list.Size());
    CHECK_FALSE(list.IsEmpty());
    CHECK_EQUAL(value, *list[0]);
    CHECK(nullptr == list[1]);
}

TEST(ListTest, PushBack_TwoItems)
{
    TestList list;
    int value1 = 5;
    int value2 = 10;

    list.PushBack(value1);
    list.PushBack(value2);

    CHECK_EQUAL(2, list.Size());
    CHECK_FALSE(list.IsEmpty());
    CHECK_EQUAL(value1, *list[0]);
    CHECK_EQUAL(value2, *list[1]);
    CHECK(nullptr == list[2]);
}

TEST(ListTest, PushFront_OneItem)
{
    TestList list;
    int value = 5;

    list.PushFront(value);

    CHECK_EQUAL(1, list.Size());
    CHECK_FALSE(list.IsEmpty());
    CHECK_EQUAL(value, *list[0]);
    CHECK(nullptr == list[1]);
}

TEST(ListTest, PushFront_TwoItems)
{
    TestList list;
    int value1 = 5;
    int value2 = 10;

    list.PushFront(value1);
    list.PushFront(value2);

    CHECK_EQUAL(2, list.Size());
    CHECK_FALSE(list.IsEmpty());
    CHECK_EQUAL(value2, *list[0]);
    CHECK_EQUAL(value1, *list[1]);
    CHECK(nullptr == list[2]);
}

TEST(ListTest, PopBack_OneItem)
{
    TestList list;
    int value = 5;

    list.PushBack(value);

    CHECK(list.PopBack());
    CHECK_FALSE(list.PopBack());

    CHECK_EQUAL(0, list.Size());
    CHECK(list.IsEmpty());
    CHECK(nullptr == list[0]);
}

TEST(ListTest, PopBack_AndPush)
{
    TestList list;
    int value = 5;

    list.PushBack(value);
    CHECK(list.PopBack());
    list.PushBack(value+1);

    CHECK_EQUAL(1, list.Size());
    CHECK_EQUAL((value + 1), *list[0]);
}

TEST(ListTest, PopFront_OneItem)
{
    TestList list;
    int value = 5;

    list.PushBack(value);

    CHECK(list.PopFront());
    CHECK_FALSE(list.PopFront());

    CHECK_EQUAL(0, list.Size());
    CHECK(list.IsEmpty());
    CHECK(nullptr == list[0]);
}

TEST(ListTest, PopFront_AndPush)
{
    TestList list;
    int value = 5;

    list.PushBack(value);
    CHECK(list.PopFront());
    list.PushBack(value+1);

    CHECK_EQUAL(1, list.Size());
    CHECK_EQUAL((value + 1), *list[0]);
}

TEST(ListTest, At)
{
    List<char> list;

    list.PushBack('a');
    list.PushBack('b');
    list.PushBack('c');

    CHECK_EQUAL(0, list.At('a'));
    CHECK_EQUAL(1, list.At('b'));
    CHECK_EQUAL(2, list.At('c'));
    CHECK_EQUAL(-1, list.At('d'));
}

TEST(ListTest, Remove)
{
    List<char> list;

    list.PushBack('a');
    list.PushBack('b');
    list.PushBack('c');

    CHECK(list.Remove(1));

    CHECK_EQUAL(0, list.At('a'));
    CHECK_EQUAL(-1, list.At('b'));
    CHECK_EQUAL(1, list.At('c'));
}

TEST(ListTest, Remove_Head)
{
    List<char> list;

    list.PushBack('a');
    list.PushBack('b');
    list.PushBack('c');

    CHECK(list.Remove(0));

    CHECK_EQUAL(-1, list.At('a'));
    CHECK_EQUAL(0, list.At('b'));
    CHECK_EQUAL(1, list.At('c'));
}

TEST(ListTest, Remove_Tail)
{
    List<char> list;

    list.PushBack('a');
    list.PushBack('b');
    list.PushBack('c');

    CHECK(list.Remove(2));

    CHECK_EQUAL(0, list.At('a'));
    CHECK_EQUAL(1, list.At('b'));
    CHECK_EQUAL(-1, list.At('c'));
}