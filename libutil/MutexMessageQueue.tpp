#pragma once

namespace util
{
	template<typename T, class B, class S>
	MutexMessageQueueBase<T, B, S>::MutexMessageQueueBase(size_t size)
		: MessageQueueBase<T, B, S>(size)
		, _mutex()
	{
	}


	template<typename T, class B, class S>
	bool MutexMessageQueueBase<T, B, S>::enqueue(const T &element)
	{
		_mutex.lock();
		auto result = MessageQueueBase<T, B, S>::enqueue(element);
		_mutex.unlock();

		return result;
	}

	template<typename T, class B, class S>
	bool MutexMessageQueueBase<T, B, S>::tryEnqueue(const T &element)
	{
		if (_mutex.try_lock() == false)
			return false;

		auto result = MessageQueueBase<T, B, S>::enqueue(element);
		_mutex.unlock();

		return result;
	}

	template<typename T, class B, class S>
	bool MutexMessageQueueBase<T, B, S>::enqueue(const Span<T> & buffer)
	{
		_mutex.lock();
		auto result = MessageQueueBase<T, B, S>::enqueue(buffer);
		_mutex.unlock();

		return result;
	}

	template<typename T, class B, class S>
	bool MutexMessageQueueBase<T, B, S>::tryEnqueue(const Span<T> & buffer)
	{
		if (_mutex.try_lock() == false)
			return false;

		auto result = MessageQueueBase<T, B, S>::enqueue(buffer);
		_mutex.unlock();

		return result;
	}

	template<typename T, class B, class S>
	bool MutexMessageQueueBase<T, B, S>::dequeueTo(T *out)
	{
		_mutex.lock();
		auto result = MessageQueueBase<T, B, S>::dequeueTo(out);
		_mutex.unlock();

		return result;
	}

	template<typename T, class B, class S>
	bool MutexMessageQueueBase<T, B, S>::tryDequeueTo(T *out)
	{
		if (_mutex.try_lock() == false)
			return false;

		auto result = MessageQueueBase<T, B, S>::tryDequeueTo(out);
		_mutex.unlock();

		return result;
	}

	template<typename T, class B, class S>
	size_t MutexMessageQueueBase<T, B, S>::dequeueAllTo(T *out)
	{
		_mutex.lock();
		auto result = MessageQueueBase<T, B, S>::dequeueAllTo(out);
		_mutex.unlock();

		return result;
	}

	template<typename T, class B, class S>
	size_t MutexMessageQueueBase<T, B, S>::tryDequeueAllTo(T *out)
	{
		if (_mutex.try_lock() == false)
			return false;

		auto result = MessageQueueBase<T, B, S>::tryDequeueAllTo(out);
		_mutex.unlock();

		return result;
	}

	template<typename T, class B, class S>
	size_t MutexMessageQueueBase<T, B, S>::dequeueAll()
	{
		_mutex.lock();
		auto result = MessageQueueBase<T, B, S>::dequeueAll();
		_mutex.unlock();

		return result;
	}

	template<typename T, class B, class S>
	size_t MutexMessageQueueBase<T, B, S>::tryDequeueAll()
	{
		if (_mutex.try_lock() == false)
			return false;

		auto result = MessageQueueBase<T, B, S>::tryDequeueAll();
		_mutex.unlock();

		return result;
	}
}