#pragma once

/**
 * @file	Vector.hpp
 * @author	Adrian Szczepanski
 * @date	24-03-2021
 * @brief
 * @details
**/

#include <libutil/Buffer.hpp>

namespace util
{
    template<class T>
    using Vector = Buffer<T>;

	template<class T, size_t S>
    using SVector = SBuffer<T, S>;
}