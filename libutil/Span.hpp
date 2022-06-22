#pragma once

/**
 * @file	Span.hpp
 * @author	Adrian Szczepanski
 * @date	24-03-2021
 * @brief
 * @details
**/

#include <cstddef>
#include <libutil/DataUnit.hpp>
#include <algorithm>

namespace util
{
	template <typename T>
	struct Span
	{
        Span(const T*, size_t);

        constexpr auto begin() const { return _data; }
        constexpr auto end() const { return _data + _size; }
        constexpr auto rbegin() const { return _data + _size - 1; }
        constexpr auto rend() const { return _data - 1; }

        constexpr auto& operator[](size_t i) const { return _data[i]; }
        constexpr auto data() const { return _data; }

        constexpr auto size() const { return _size; }
        constexpr auto size_bytes() const { return _size * sizeof(T); }
        constexpr bool empty() const { return (_size == 0); }

        constexpr Span<T> first(size_t count) const { return { _data, count }; }
        constexpr Span<T> last(size_t count) const { return { (_data + _size) - count, count }; }
        constexpr Span<T> subspan(size_t offset, size_t count) const { return { _data + offset, count }; }

		bool operator==(const Span<T>& span);

    private:      
		const T* _data;
		size_t _size;
	};

	using ByteSpan = Span<byte>;
	using HwordSpan = Span<hword>;
	using WordSpan = Span<word>;
	using DwordSpan = Span<dword>;
}

#include <libutil/Span.tpp>