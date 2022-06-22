#pragma once

/**
 * @file	MutexQueue.hpp
 * @author	Adrian Szczepanski
 * @date	24-03-2021
 * @brief
 * @details
**/

#include <mutex>
#include <libutil/Queue.hpp>

namespace util
{
	template<typename T>
	class MutexQueue : public Queue<T>
	{
	public:
		MutexQueue(size_t);

		bool enqueue(const T &element) override;
		bool enqueue(const Span<T> &buffer) override;
		bool dequeueTo(T *, size_t count) override;
		size_t dequeueAllTo(T *) override;
		size_t dequeueAllTo(Buffer<T> &destination) override;
		
		bool tryEnqueue(const T &element);
		bool tryEnqueue(const Span<T> &buffer);
		bool tryDequeueTo(T *, size_t count);
		bool tryDequeueAllTo(T *);

	protected:
		T operator[](size_t index) { return 0; }
		T * getData(size_t index) override { return nullptr; }

	private:
		std::mutex _mutex;
	};
}

#include <libutil/MutexQueue.tpp>