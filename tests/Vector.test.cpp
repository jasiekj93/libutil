/**
 * @file Vector.test.cpp
 * @author Adrian Szczepanski
 * @date 11-08-2021
 * @brief 
 * @details
 */

#include <libUtils/Static/Vector.hpp>

#include <CppUTest/CommandLineTestRunner.h>

using namespace Utils;
using namespace Utils::Static;

static constexpr size_t SIZE = 5;

TEST_GROUP(VectorTest)
{
};

TEST(VectorTest, Empty)
{
    Vector<SIZE> vector;
    
    CHECK_EQUAL(0, vector.Count());
}

TEST(VectorTest, FromByteSpan)
{
    byte data[] = { 1, 2, 3, 4, 5 };
    ByteSpan span = { data, sizeof(data) };
    Vector<SIZE> vector(span);
    
    CHECK_EQUAL(span.size, vector.Count());
    CHECK(span == vector.ToByteSpan());
}

TEST(VectorTest, FromInitalizerList)
{
    byte data[] = { 1, 2, 3, 4, 5 };
    ByteSpan span = { data, sizeof(data) };
    Vector<SIZE> vector = { 1, 2, 3, 4, 5 };
    
    CHECK_EQUAL(5, vector.Count());
    CHECK(span == vector.ToByteSpan());
}

TEST(VectorTest, FromByteSpan_MoreThanCount)
{
    byte data[] = { 1, 2, 3, 4, 5, 6 };
    ByteSpan span = { data, sizeof(data) };
    Vector<SIZE> vector(span);
    
    CHECK_EQUAL(0, vector.Count());
}

TEST(VectorTest, Put)
{
    byte data[] = { 1, 2, 3, 4 };
    Vector<SIZE> vector({ data, sizeof(data) });

    CHECK(vector.Put(5));
    CHECK_FALSE(vector.Put(6));
    
    CHECK_EQUAL(5, vector.Count());
    CHECK_EQUAL(5, vector[4]);
}

TEST(VectorTest, Append)
{
    byte data[] = { 1, 2, 3 };
    byte appended[] = { 4, 5 };
    Vector<SIZE> vector({ data, sizeof(data) });

    CHECK(vector.Append({ appended, sizeof(appended) }));
    CHECK_FALSE(vector.Append({ appended, sizeof(appended) }));
    
    CHECK_EQUAL(5, vector.Count());
    CHECK_EQUAL(4, vector[3]);
    CHECK_EQUAL(5, vector[4]);
}