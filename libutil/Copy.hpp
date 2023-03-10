#pragma once

/**
 * @file Copy.hpp
 * @author Adrian Szczepanski
 * @date 05-09-2022
 * @brief 
 * @details
 */

#include <cstdint>
#include <cstddef>
#include <cstring>
#include <algorithm>

namespace util
{
    constexpr void* memcpy(void* dest, const void* src, size_t size)
    {
    #ifdef NOT_USE_STD 
        auto destination = (uint8_t*)dest;
        auto source = (const uint8_t*)src;

        for(auto i = 0U; i < size; i++)
            destination[i] = source[i];

        return dest;
    #else
        return std::memcpy(dest, src, size);
    #endif
    }

    constexpr void* memset(void* dest, int value, size_t size)
    {
    #ifdef NOT_USE_STD 
        auto destination = (uint8_t*)dest;

        for(auto i = 0U; i < size; i++)
            destination[i] = value;

        return dest;
    #else
        return std::memset(dest, value, size);
    #endif
    }

    constexpr char* strncat(char* dest, const char* src, size_t size)
    {
    #ifdef NOT_USE_STD 
        auto ptr = dest + strlen(dest);
    
        while (*src != '\0' && size > 0U) 
        {
            *ptr++ = *src++;
            size--;
        }
    
        // null terminate destination string
        *ptr = '\0';
    
        // the destination is returned by standard `strcat()`
        return dest;
    #else
        return std::strncat(dest, src, size);
    #endif
    }

    template<typename T>
    constexpr void copy(const T* first, const T* last, T* result)
    {
    #ifdef NOT_USE_STD
        while(first != last)
        {
            *result = *first;

            first++;
            result++;
        }
    #else
        std::copy(first, last, result);
    #endif
    }

    template<typename T>
    constexpr void reverse(T* first, T* last)
    {
    #ifdef NOT_USE_STD
        last--;
        while (first < last)
        {
            T temp = *first;
            *first = *last;
            *last = temp;

            first++;
            last--;
        } 
    #else
        std::reverse(first, last);
    #endif
    }
}