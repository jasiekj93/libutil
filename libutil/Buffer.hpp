#pragma once

/**
 * @file	Buffer.hpp
 * @author	Adrian Szczepanski
 * @date	24-03-2021
 * @brief
 * @details
**/

#include <libutil/Array.hpp>

namespace util
{
	template <class T, class Container>
	class BufferBase
	{
	public:
		explicit BufferBase(size_t);
		BufferBase(size_t, const Span<T>&);
        BufferBase(size_t, std::initializer_list<T>);
		BufferBase();
		BufferBase(const Span<T>&);
        BufferBase(std::initializer_list<T>);

		bool add(const Span<T>&);
		bool add(const T&);
		bool add(const T*, size_t);

		bool insert(size_t index, const Span<T>&);
		bool insert(size_t index, const T&);
		bool insert(size_t index, const T*, size_t);

		constexpr void clear() { _count = 0; }
		void deepClear();
		bool shrink(size_t size);
		bool shiftLeft(size_t startPosition, size_t count);

        bool operator==(const BufferBase&) const;
        constexpr bool operator!=(const BufferBase& b) const { return !(*this == b); }

		constexpr auto data() const { return _storage.data(); }
		constexpr auto data() { return _storage.data(); }
		constexpr auto data(size_t i) const { return _storage.data() + i; }
		constexpr auto count() const { return _count; }
		constexpr auto capacity() const { return _storage.size(); }
		constexpr auto size() const { return _storage.size(); }
		constexpr bool isFull() const { return (_count == _storage.size()); }
		constexpr bool isEmpty() const { return (_count == 0); }
		constexpr bool isNotEmpty() const { return (_count != 0); }
		constexpr auto toSpan() const { return _storage.toSpan(); }

		constexpr auto operator[](size_t i) const { return _storage[i]; }
		constexpr auto operator[](size_t i) { return _storage[i]; }
        constexpr auto& front() { return _storage.front(); }
        constexpr auto& front() const { return _storage.front(); }
        constexpr auto& back() { return _storage[_count - 1]; }
        constexpr auto& back() const { return _storage[_count - 1]; }
		constexpr auto begin() { return _storage.begin(); }
		constexpr auto end() { return _storage.end(); }
		constexpr auto cbegin() const { return _storage.cbegin(); }
		constexpr auto cend() const { return _storage.cend(); }

	private:
        Container _storage;
		size_t _count;
	};

	template<class T>
	using Buffer = BufferBase<T, DynArray<T>>;

	template<class T, size_t S>
	using SBuffer = BufferBase<T, Array<T, S>>;
}

#include <libutil/Buffer.tpp>
