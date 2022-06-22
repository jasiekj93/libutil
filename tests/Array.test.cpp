
// /**
//  * @file Array.test.cpp
//  * @author Adrian Szczepanski
//  * @date 11-08-2021
//  * @brief 
//  * @details
//  */

// #include <libutil/Array.hpp>

// #include <CppUTest/CommandLineTestRunner.h>

// using namespace util;

// static constexpr size_t SIZE = 5;

// TEST_GROUP(ArrayTest)
// {
// };

// TEST(ArrayTest, DynArray_Swap)
// {
//    DynArray<byte> arr1(4, { 1, 2, 3, 4 }); 
//    DynArray<byte> arr2(4, { 10, 20, 30, 40 }); 

//    auto arr1Copy = arr1;
//    auto arr2Copy = arr2;

//    arr1Copy.swap(arr2Copy);

//    CHECK(arr1Copy == arr2);
//    CHECK(arr2Copy == arr1);
// }