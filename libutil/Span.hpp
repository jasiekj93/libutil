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
		const T *data;
		size_t size;


		bool operator==(const Span<T> &span)
		{
			if(this->size == span.size)
                return std::equal(this->data, this->data + this->size, span.data);
			else
				return false;
		}
	};

	using ByteSpan = Span<byte>;
	using HwordSpan = Span<hword>;
	using WordSpan = Span<word>;
	using DwordSpan = Span<dword>;
}