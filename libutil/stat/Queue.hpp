#pragma once

/**
 * @file	Queue.hpp
 * @author	Adrian Szczepanski
 * @date	24-03-2021
 * @brief
 * @details
**/

#include <libutil/stat/Buffer.hpp>

namespace util::stat
{
	template<typename T, size_t SIZE>
	class Queue
	{
	public:
		Queue();

		virtual inline bool enqueue(const T &element) { return _buffer.add(element); }
		virtual inline bool enqueue(const Span<T> & buffer) { return _buffer.add(buffer); }
		virtual bool dequeueTo(T *, size_t count);
		inline virtual bool dequeue(size_t count) { return _buffer.shiftLeft(0, count); }
		virtual size_t dequeueAllTo(T *);
		virtual size_t dequeueAllTo(Buffer<T, SIZE> &);
		virtual size_t dequeueAll();

		virtual inline bool pushBack(const T &obj) { return _buffer.add(obj); }
		virtual inline bool pushFront(const T &obj) { return _buffer.insert(0, obj); }
		virtual T popBack();
		virtual T popFront();

        virtual const auto & getBuffer() const { return _buffer; }

	protected:
		Buffer<T, SIZE> _buffer;
	};
}

#include <libutil/stat/Queue.tpp>