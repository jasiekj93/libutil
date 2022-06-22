#pragma once

namespace util::stat
{
	template<typename T, uint32_t SIZE>
	MutexMessageQueue<T, SIZE>::MutexMessageQueue()
		: MessageQueue<T, SIZE>()
		, _mutex()
	{
	}


	template<typename T, uint32_t SIZE>
	bool MutexMessageQueue<T, SIZE>::enqueue(const T &element)
	{
		_mutex.lock();
		auto result = MessageQueue<T, SIZE>::enqueue(element);
		_mutex.unlock();

		return result;
	}

	template<typename T, uint32_t SIZE>
	bool MutexMessageQueue<T, SIZE>::tryEnqueue(const T &element)
	{
		if (_mutex.try_lock() == false)
			return false;

		auto result = MessageQueue<T, SIZE>::enqueue(element);
		_mutex.unlock();

		return result;
	}

	template<typename T, uint32_t SIZE>
	bool MutexMessageQueue<T, SIZE>::enqueue(const Span<T> & buffer)
	{
		_mutex.lock();
		auto result = MessageQueue<T, SIZE>::enqueue(buffer);
		_mutex.unlock();

		return result;
	}

	template<typename T, uint32_t SIZE>
	bool MutexMessageQueue<T, SIZE>::tryEnqueue(const Span<T> & buffer)
	{
		if (_mutex.try_lock() == false)
			return false;

		auto result = MessageQueue<T, SIZE>::enqueue(buffer);
		_mutex.unlock();

		return result;
	}

	template<typename T, uint32_t SIZE>
	bool MutexMessageQueue<T, SIZE>::dequeueTo(T *out)
	{
		_mutex.lock();
		auto result = MessageQueue<T, SIZE>::dequeueTo(out);
		_mutex.unlock();

		return result;
	}

	template<typename T, uint32_t SIZE>
	bool MutexMessageQueue<T, SIZE>::tryDequeueTo(T *out)
	{
		if (_mutex.try_lock() == false)
			return false;

		auto result = MessageQueue<T, SIZE>::tryDequeueTo(out);
		_mutex.unlock();

		return result;
	}

	template<typename T, uint32_t SIZE>
	size_t MutexMessageQueue<T, SIZE>::dequeueAllTo(T *out)
	{
		_mutex.lock();
		auto result = MessageQueue<T, SIZE>::dequeueAllTo(out);
		_mutex.unlock();

		return result;
	}

	template<typename T, uint32_t SIZE>
	size_t MutexMessageQueue<T, SIZE>::tryDequeueAllTo(T *out)
	{
		if (_mutex.try_lock() == false)
			return false;

		auto result = MessageQueue<T, SIZE>::tryDequeueAllTo(out);
		_mutex.unlock();

		return result;
	}

	template<typename T, uint32_t SIZE>
	size_t MutexMessageQueue<T, SIZE>::dequeueAll()
	{
		_mutex.lock();
		auto result = MessageQueue<T, SIZE>::dequeueAll();
		_mutex.unlock();

		return result;
	}

	template<typename T, uint32_t SIZE>
	size_t MutexMessageQueue<T, SIZE>::tryDequeueAll()
	{
		if (_mutex.try_lock() == false)
			return false;

		auto result = MessageQueue<T, SIZE>::tryDequeueAll();
		_mutex.unlock();

		return result;
	}
}