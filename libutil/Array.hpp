#pragma once

#include <libutil/Span.hpp>

namespace util
{
    template<typename T, size_t N>
    class Array : public std::array<T, N>
    {
    public:
        using std::array<T, N>::array;

        inline Span<T> toSpan() const { return { data(), size() }; }   
    };

    template<size_t N>
    using ByteArray = Array<byte, N>;
    template<size_t N>
    using HwordArray = Array<hword, N>;
    template<size_t N>
    using WordArray = Array<word, N>;
    template<size_t N>
    using DwordArray = Array<dword, N>;
}