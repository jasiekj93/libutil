#pragma once

/**
 * @file MessageQueue.hpp
 * @author Adrian Szczepanski
 * @date 22-06-2022
 * @brief 
 * @details
 */

#include <libutil/Queue.hpp>

namespace util
{
	template<typename T, class TBuffer, class SizeBuffer>
		class MessageQueueBase
		{		
		public:
			MessageQueueBase(size_t size);
		
			virtual bool enqueue(const T&);
			virtual bool enqueue(const Span<T>&);
			virtual bool dequeueTo(T*);
			virtual void dequeue();
			virtual size_t dequeueAllTo(T*);
			virtual size_t dequeueAll();
			
			constexpr auto firstMessageSize() const { return (_sizes.isEmpty() ? 0 : _sizes.front()); }
			constexpr auto messageCount() const { return _sizes.count(); }
			
			constexpr size_t count() const { return _objects.count(); }
			constexpr size_t size() const { return _objects.size(); }

		private:
			QueueBase<T, TBuffer> _objects;
			QueueBase<size_t, SizeBuffer> _sizes;
		};
    
    template<typename T>
    using MessageQueue = MessageQueueBase<T, Buffer<T>, Buffer<size_t>>;

    template<typename T, size_t SIZE>
    using SMessageQeueue = MessageQueueBase<T, SBuffer<T, SIZE>, SBuffer<size_t, SIZE>>;
}

#include <libutil/MessageQueue.tpp>