#pragma once

/**
 * @file	Buffer.hpp
 * @author	Adrian Szczepanski
 * @date	24-03-2021
 * @brief
 * @details
**/

#include <libutil/Container.hpp>
#include <libutil/Span.hpp>

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

		inline const T* data() const { return _storage.data(); }
		inline T* data() { return _storage.data(); }
		inline T* data(size_t i) { return _storage.data() + i; }
		inline auto count() const { return _count; }
		inline auto capacity() const { return _storage.size(); }
		inline bool isFull() const { return (_count == _storage.size()); }
		inline bool isEmpty() const { return (_count == 0); }
		inline bool isNotEmpty() const { return (_count != 0); }
		inline Span<T> toSpan() const { return Span<T>{ _storage.data(), _count }; }

		inline const T& operator[](size_t i) const { return _storage[i]; }
		inline T* begin() { return _storage[0]; }
		inline T* end() { return _storage[_count]; }
		inline const T* cbegin() const { return _storage[0]; }
		inline const T* cend() const { return _storage[_count]; }

	private:
	 	Container _storage;
		size_t _count;
	};

	template<class T>
	using Buffer = BufferBase<T, DynamicContainer<T>>;

	template<class T, size_t S>
	using SBuffer = BufferBase<T, StaticContainer<T, S>>;

    template<class T>
    using Vector = Buffer<T>;

	template<class T, size_t S>
    using SVector = SBuffer<T, S>;
}

#include <libutil/Buffer.tpp>
