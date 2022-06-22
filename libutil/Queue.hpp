#pragma once

/**
 * @file	Queue.hpp
 * @author	Adrian Szczepanski
 * @date	24-03-2021
 * @brief
 * @details
**/

#include <libutil/Buffer.hpp>

namespace util
{
	template<typename T>
	class Queue
	{
	public:
		Queue(size_t);

		virtual inline bool enqueue(const T &element) { return _buffer.add(element); }
		virtual inline bool enqueue(const Span<T> & buffer) { return _buffer.add(buffer); }
		virtual bool dequeueTo(T *, size_t count);
		inline virtual bool dequeue(size_t count) { return _buffer.shiftLeft(0, count); }
		virtual size_t dequeueAllTo(T *);
		virtual size_t dequeueAllTo(Buffer<T> &);
		virtual size_t dequeueAll();

		virtual inline bool pushBack(const T &obj) { return _buffer.add(obj); }
		virtual inline bool pushFront(const T &obj) { return _buffer.insert(0, obj); }
		virtual T popBack();
		virtual T popFront();
		virtual inline const T & front() const { return _buffer[0]; }
		virtual inline const T & back() const { return _buffer[_buffer.count() - 1]; }
		virtual inline void clear() { _buffer.clear(); }

		virtual inline size_t getSize() const { return _buffer.capacity(); }
		virtual inline size_t getCount() const { return _buffer.count(); }
		virtual inline size_t getFreeSize() const { return (_buffer.capacity() - _buffer.count()); }
		virtual inline bool isEmpty() const { return (_buffer.count() == 0); }
		virtual inline bool isNotEmpty() const { return (_buffer.count() != 0); }
		virtual inline bool isFull() const { return (_buffer.count() == _buffer.capacity()); }

		virtual inline T operator[](size_t index) const { return _buffer[index]; }
		virtual inline const T * data(size_t index) const { return _buffer.data(index); }
		virtual inline const T * data() const { return _buffer.data(); }

	protected:
		Buffer<T> _buffer;
	};
}

#include <libutil/Queue.tpp>
