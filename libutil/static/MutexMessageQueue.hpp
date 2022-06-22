#pragma once

#include <libUtils/Static/MessageQueue.hpp>
#include <libUtils/Mutex.hpp>

namespace Utils::Static
{
	template<typename T, uint32_t SIZE>
		class MutexMessageQueue : public MessageQueue<T, SIZE>
		{
		private:
			Mutex _mutex;
		
		public:
			MutexMessageQueue();
		
			bool Enqueue(const T &element) override;
			bool TryEnqueue(const T &element);
			bool Enqueue(const Span<T> & buffer) override;
			bool TryEnqueue(const Span<T> & buffer);
			bool DequeueTo(T *) override;
			bool TryDequeueTo(T *);
			size_t DequeueAllTo(T *) override;
			size_t TryDequeueAllTo(T *);
			size_t DequeueAll() override;
			size_t TryDequeueAll();
		};
}

#include <libUtils/Static/MutexMessageQueue.tpp>