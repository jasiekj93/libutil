#pragma once

/**
 * @file MessageQueue.hpp
 * @author Adrian Szczepanski
 * @date 22-06-2022
 * @brief 
 * @details
 */

#include <libutil/stat/Queue.hpp>

namespace util::stat
{
	template<typename T, size_t SIZE>
		class MessageQueue
		{		
		public:
			MessageQueue();
		
			virtual bool enqueue(const T &element);
			virtual bool enqueue(const Span<T> & buffer);
			virtual bool dequeueTo(T *);
			virtual void dequeue();
			virtual size_t dequeueAllTo(T *);
			virtual size_t dequeueAll();
			
			inline size_t firstMessageSize() const { return (_sizes.isEmpty() ? 0 : _sizes.front()); }
			inline size_t messageCount() const { return _sizes.getCount(); }
			
			inline size_t count() const { return _objects.getCount(); }
			inline size_t size() const { return SIZE; }

		private:
			Queue<T, SIZE> _objects;
			Queue<size_t, SIZE> _sizes;
		};
}

#include <libutil/stat/MessageQueue.tpp>