#pragma once

#include <libUtils/Static/Queue.hpp>

namespace Utils::Static
{
	template<typename T, size_t SIZE>
		class MessageQueue
		{		
		public:
			MessageQueue();
		
			virtual bool Enqueue(const T &element);
			virtual bool Enqueue(const Span<T> & buffer);
			virtual bool DequeueTo(T *);
			virtual void Dequeue();
			virtual size_t DequeueAllTo(T *);
			virtual size_t DequeueAll();
			
			inline size_t GetFirstMessageSize() const { return (_sizes.IsEmpty() ? 0 : _sizes.Front()); }
			inline size_t GetMessageCount() const { return _sizes.GetCount(); }
			
			inline size_t GetCount() const { return _objects.GetCount(); }
			inline size_t GetSize() const { return SIZE; }

		private:
			Queue<T, SIZE> _objects;
			Queue<size_t, SIZE> _sizes;
		};
}

#include <libUtils/Static/MessageQueue.tpp>