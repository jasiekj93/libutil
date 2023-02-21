/**
 * @file Copy.test.cpp
 * @author Adrian Szczepanski
 * @date 21-02-2023
 * @brief 
 * @details
 */

#include <libutil/Copy.hpp>
#include <libutil/Array.hpp>

#include <CppUTest/CommandLineTestRunner.h>

using namespace util;

TEST_GROUP(CopyTest)
{
};

#define NOT_USE_STD

TEST(CopyTest, reverse_odd)
{
    util::Array<unsigned char, 5> input = { 1, 2, 3, 4, 5 };
    util::Array<unsigned char, 5> expected = { 5, 4, 3, 2, 1 };

    reverse(input.begin(), input.end());
    CHECK(expected == input);
    MEMCMP_EQUAL(expected.data(), input.data(), 5);
}

TEST(CopyTest, reverse_even)
{
    util::Array<unsigned char, 6> input = { 1, 2, 3, 4, 5, 6 };
    util::Array<unsigned char, 6> expected = { 6, 5, 4, 3, 2, 1 };

    reverse(input.begin(), input.end());

    CHECK(expected == input);
    MEMCMP_EQUAL(expected.data(), input.data(), 6);
}

TEST(CopyTest, copy)
{
    util::Array<unsigned char, 6> input = { 1, 2, 3, 4, 5, 6 };
    util::Array<unsigned char, 6> output = { 0 };

    copy(input.begin(), input.end(), output.begin());

    CHECK(output == input);
}

TEST(CopyTest, memset)
{
    util::Array<unsigned char, 6> input = { 1, 2, 3, 4, 5, 6 };
    util::Array<unsigned char, 6> expected = { 0, 0, 0, 0, 0, 0 };

    util::memset(input.data(), 0, input.size());

    CHECK(expected == input);
}

TEST(CopyTest, memcpy)
{
    util::Array<unsigned char, 6> input = { 1, 2, 3, 4, 5, 6 };
    util::Array<unsigned char, 6> output = { 0 };

    util::memcpy(output.data(), input.data(), input.size());

    CHECK(output == input);
}