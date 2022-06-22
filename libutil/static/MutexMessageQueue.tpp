#pragma once

namespace Utils::Static
{
	template<typename T, uint32_t SIZE>
	MutexMessageQueue<T, SIZE>::MutexMessageQueue()
		: MessageQueue<T, SIZE>()
		, _mutex()
	{
	}


	template<typename T, uint32_t SIZE>
	bool MutexMessageQueue<T, SIZE>::Enqueue(const T &element)
	{
		_mutex.Lock();
		auto result = MessageQueue<T, SIZE>::Enqueue(element);
		_mutex.Unlock();

		return result;
	}

	template<typename T, uint32_t SIZE>
	bool MutexMessageQueue<T, SIZE>::TryEnqueue(const T &element)
	{
		if (_mutex.TryLock() == false)
			return false;

		auto result = MessageQueue<T, SIZE>::Enqueue(element);
		_mutex.Unlock();

		return result;
	}

	template<typename T, uint32_t SIZE>
	bool MutexMessageQueue<T, SIZE>::Enqueue(const Span<T> & buffer)
	{
		_mutex.Lock();
		auto result = MessageQueue<T, SIZE>::Enqueue(buffer);
		_mutex.Unlock();

		return result;
	}

	template<typename T, uint32_t SIZE>
	bool MutexMessageQueue<T, SIZE>::TryEnqueue(const Span<T> & buffer)
	{
		if (_mutex.TryLock() == false)
			return false;

		auto result = MessageQueue<T, SIZE>::Enqueue(buffer);
		_mutex.Unlock();

		return result;
	}

	template<typename T, uint32_t SIZE>
	bool MutexMessageQueue<T, SIZE>::DequeueTo(T *out)
	{
		_mutex.Lock();
		auto result = MessageQueue<T, SIZE>::DequeueTo(out);
		_mutex.Unlock();

		return result;
	}

	template<typename T, uint32_t SIZE>
	bool MutexMessageQueue<T, SIZE>::TryDequeueTo(T *out)
	{
		if (_mutex.TryLock() == false)
			return false;

		auto result = MessageQueue<T, SIZE>::TryDequeueTo(out);
		_mutex.Unlock();

		return result;
	}

	template<typename T, uint32_t SIZE>
	size_t MutexMessageQueue<T, SIZE>::DequeueAllTo(T *out)
	{
		_mutex.Lock();
		auto result = MessageQueue<T, SIZE>::DequeueAllTo(out);
		_mutex.Unlock();

		return result;
	}

	template<typename T, uint32_t SIZE>
	size_t MutexMessageQueue<T, SIZE>::TryDequeueAllTo(T *out)
	{
		if (_mutex.TryLock() == false)
			return false;

		auto result = MessageQueue<T, SIZE>::TryDequeueAllTo(out);
		_mutex.Unlock();

		return result;
	}

	template<typename T, uint32_t SIZE>
	size_t MutexMessageQueue<T, SIZE>::DequeueAll()
	{
		_mutex.Lock();
		auto result = MessageQueue<T, SIZE>::DequeueAll();
		_mutex.Unlock();

		return result;
	}

	template<typename T, uint32_t SIZE>
	size_t MutexMessageQueue<T, SIZE>::TryDequeueAll()
	{
		if (_mutex.TryLock() == false)
			return false;

		auto result = MessageQueue<T, SIZE>::TryDequeueAll();
		_mutex.Unlock();

		return result;
	}
}