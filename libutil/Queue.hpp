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
	template<typename T, class Buffer>
	class QueueBase
	{
	public:
		explicit QueueBase(size_t);

		virtual inline bool enqueue(const T& element) { return _buffer.add(element); }
		virtual inline bool enqueue(const Span<T>& buffer) { return _buffer.add(buffer); }
		virtual bool dequeueTo(T*, size_t count);
		inline virtual bool dequeue(size_t count) { return _buffer.shiftLeft(0, count); }
		virtual size_t dequeueAllTo(T*);
		virtual size_t dequeueAllTo(Buffer&);
		virtual size_t dequeueAll();

		virtual inline bool pushBack(const T& obj) { return _buffer.add(obj); }
		virtual inline bool pushFront(const T& obj) { return _buffer.insert(0, obj); }
		virtual T popBack();
		virtual T popFront();
		virtual inline const T& front() const { return _buffer.front(); }
		virtual inline const T& back() const { return _buffer.back(); }
		virtual inline void clear() { _buffer.clear(); }

		virtual inline size_t size() const { return _buffer.capacity(); }
		virtual inline size_t count() const { return _buffer.count(); }
		virtual inline size_t freeSize() const { return (_buffer.capacity() - _buffer.count()); }
		virtual inline bool isEmpty() const { return (_buffer.count() == 0); }
		virtual inline bool isNotEmpty() const { return (_buffer.count() != 0); }
		virtual inline bool isFull() const { return (_buffer.count() == _buffer.capacity()); }

		virtual inline T operator[](size_t index) const { return _buffer[index]; }
		virtual inline const T * data(size_t index) const { return _buffer.data(index); }
		virtual inline const T * data() const { return _buffer.data(); }

	protected:
		Buffer _buffer;
	};


    template<typename T>
    using Queue = QueueBase<T, Buffer<T>>;
    
    template<typename T, size_t SIZE>
    using SQueue = QueueBase<T, SBuffer<T, SIZE>>;
}

#include <libutil/Queue.tpp>
