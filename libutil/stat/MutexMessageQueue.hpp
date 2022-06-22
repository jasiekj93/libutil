#pragma once

#include <libutil/stat/MessageQueue.hpp>
#include <mutex>

namespace util::stat
{
	template<typename T, uint32_t SIZE>
		class MutexMessageQueue : public MessageQueue<T, SIZE>
		{
		public:
			MutexMessageQueue();
		
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
}

#include <libutil/stat/MutexMessageQueue.tpp>