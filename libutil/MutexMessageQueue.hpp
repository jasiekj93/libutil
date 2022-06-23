#pragma once

#include <libutil/MessageQueue.hpp>
#include <mutex>

namespace util
{
	template<typename T, class TBuffer, class SizeBuffer>
		class MutexMessageQueueBase : public MessageQueueBase<T, TBuffer, SizeBuffer>
		{
		public:
			MutexMessageQueueBase(size_t = 0);
		
			bool enqueue(const T &element) override;
			bool tryEnqueue(const T &element);
			bool enqueue(const Span<T> & buffer) override;
			bool tryEnqueue(const Span<T> & buffer);
			bool dequeueTo(T *) override;
			bool tryDequeueTo(T *);
			size_t dequeueAllTo(T *) override;
			size_t tryDequeueAllTo(T *);
			size_t dequeueAll() override;
			size_t tryDequeueAll();

        private:
			std::mutex _mutex;
		};

    template<typename T>
    using MutexMessageQueue = MutexMessageQueueBase<T, Buffer<T>, Buffer<size_t>>;

    template<typename T, size_t S>
    using SMutexMessageQueue = MutexMessageQueueBase<T, SBuffer<T, S>, SBuffer<size_t, S>>;
}

#include <libutil/MutexMessageQueue.tpp>