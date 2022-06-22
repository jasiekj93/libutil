#pragma once

/**
 * @file	Buffer.hpp
 * @author	Adrian Szczepanski
 * @date	24-03-2021
 * @brief
 * @details
**/

#include <array>
#include <libutil/Span.hpp>

namespace util::stat
{
    template<typename T, size_t SIZE>
	class Buffer
	{
	public:
		Buffer();
        Buffer(const Span<T>&);
        Buffer(std::initializer_list<T>);

		bool add(const Span<T> &);
		bool add(const T &);
		bool add(const T *, size_t);

		bool insert(size_t index, const Span<T> &);
		bool insert(size_t index, const T &);
		bool insert(size_t index, const T *, size_t);

		inline void clear() { _count = 0; }
		void deepClear();
		bool shrink(size_t size);
		bool shiftLeft(size_t startPosition, size_t count);

		inline Span<T> toSpan() const { return Span<T>{ _data, _count }; }

		inline auto data() const { return _data; }
		inline auto data(size_t i) const { return &_data[i]; }
		inline auto count() const { return _count; }
		inline auto capacity() const { return SIZE; }
		inline bool isFull() const { return (_count == SIZE); }
		inline bool isEmpty() const { return (_count == 0); }
		inline bool isNotEmpty() const { return (_count != 0); }

		inline const T & operator[](size_t i) const { return _data[i]; }
		inline T & begin() { return _data[0]; }
		inline T & end() { return _data[_count]; }
		inline const T & cbegin() const { return _data[0]; }
		inline const T & cend() const { return _data[_count]; }
        constexpr const T & front() const { return _data[0]; }
        constexpr const T & back() const { return _data[_count - 1]; }

	private:
		T _data[SIZE];
		size_t _count;
	};


    template<typename T, size_t S>
    using Vector = Buffer<T, S>;
}

#include <libutil/stat/Buffer.tpp>