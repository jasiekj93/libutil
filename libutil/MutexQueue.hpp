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
	template<typename T, class Buffer>
	class MutexQueueBase : public QueueBase<T, Buffer>
	{
	public:
		explicit MutexQueueBase(size_t = 0);

		bool enqueue(const T&) override;
		bool enqueue(const Span<T>&) override;
		bool dequeueTo(T*, size_t count) override;
		size_t dequeueAllTo(T*) override;
		size_t dequeueAllTo(Buffer&) override;
		
		bool tryEnqueue(const T&);
		bool tryEnqueue(const Span<T>&);
		bool tryDequeueTo(T*, size_t count);
		bool tryDequeueAllTo(T*);

	protected:
		T operator[](size_t index) { return 0; }
		const T* data(size_t index) const override { return nullptr; }

	private:
		std::mutex _mutex;
	};

    template<typename T>
    using MutexQueue = MutexQueueBase<T, Buffer<T>>;

    template<typename T, size_t SIZE>
    using SMutexQueue = MutexQueueBase<T, SBuffer<T, SIZE>>;
}

#include <libutil/MutexQueue.tpp>