#pragma once

/**
 * @file	Mutex.hpp
 * @author	Adrian Szczepanski
 * @date	24-03-2021
 * @brief
 * @details
**/

#include <atomic>

namespace util
{
	class Mutex
	{
	public:
		Mutex() { atomic_flag_clear(&_guard); }

		inline bool try_lock() { return !atomic_flag_test_and_set(&_guard); }
		inline void lock() { do {} while (try_lock()); }
		inline void unlock() { atomic_flag_clear(&_guard); }

	private:
		volatile std::atomic_flag _guard;
	};

}