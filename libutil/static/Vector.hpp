#pragma once

/**
 * @file Vector.hpp
 * @author Adrian Szczepanski
 * @date 12-08-2021
 * @brief 
 * @details
 */

#include <libUtils/Span.hpp>
#include <utility>

namespace Utils::Static
{
    template<size_t SIZE>
    class Vector
    {
    public:
        Vector();
        Vector(const ByteSpan &);
        Vector(std::initializer_list<byte>);

        bool Put(byte);
        bool Append(const ByteSpan &);
        inline void Clear() { _count = 0; }
        
        inline auto Data() const { return _data; }
        inline auto Count() const { return _count; }
        inline ByteSpan ToByteSpan() const { return { _data, _count }; }
        
        bool operator==(const Vector &) const;
        bool operator!=(const Vector &) const;
        inline auto operator[](size_t i) const { return _data[i]; }

        inline auto begin() const { return _data; }
        inline auto end() const { return &_data[_count]; }

    protected:
        byte _data[SIZE];
        size_t _count;
    };
}

#include <libUtils/Static/Vector.tpp>