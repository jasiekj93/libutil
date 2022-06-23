#pragma once

namespace util
{
	template<typename T, class B>
	MutexQueueBase<T, B>::MutexQueueBase(size_t size)
		: QueueBase<T, B>(size)
		, _mutex()
	{
	}

	template<typename T, class B>
	bool MutexQueueBase<T, B>::enqueue(const Span<T> &buffer)
	{
		_mutex.lock();
		auto result = QueueBase<T, B>::enqueue(buffer);
		_mutex.unlock();

		return result;
	}

	template<typename T, class B>	
	bool MutexQueueBase<T, B>::enqueue(const T &element)
	{
		_mutex.lock();
		auto result = QueueBase<T, B>::enqueue(element);
		_mutex.unlock();

		return result;
	}

	template<typename T, class B>
	size_t MutexQueueBase<T, B>::dequeueAllTo(T *destination)
	{
		_mutex.lock();
		auto result = QueueBase<T, B>::dequeueAllTo(destination);
		_mutex.unlock();

		return result;
	}

	template<typename T, class B>
	size_t MutexQueueBase<T, B>::dequeueAllTo(B &destination)
	{
		_mutex.lock();
		auto result = QueueBase<T, B>::dequeueAllTo(destination);
		_mutex.unlock();

		return result;
	}

	template<typename T, class B>
	bool MutexQueueBase<T, B>::dequeueTo(T *destination, size_t count)
	{
		_mutex.lock();
		bool result = QueueBase<T, B>::dequeueTo(destination, count);
		_mutex.unlock();

		return result;
	}

	template<typename T, class B>	
	bool MutexQueueBase<T, B>::tryEnqueue(const Span<T> &buffer)
	{
		bool result;

		if (_mutex.try_lock() == false)
			return false;

		result = QueueBase<T, B>::enqueue(buffer);
		_mutex.unlock();

		return result;
	}

	template<typename T, class B>
	bool MutexQueueBase<T, B>::tryEnqueue(const T &element)
	{
		bool result;

		if (_mutex.try_lock() == false)
			return false;

		result = QueueBase<T, B>::enqueue(element);
		_mutex.unlock();

		return result;
	}

	template<typename T, class B>
	bool MutexQueueBase<T, B>::tryDequeueAllTo(T *destination)
	{
		if (_mutex.try_lock() == false)
			return false;

		QueueBase<T, B>::dequeueAllTo(destination);
		_mutex.unlock();

		return true;
	}

	template<typename T, class B>
	bool MutexQueueBase<T, B>::tryDequeueTo(T *destination, size_t count)
	{
		if (_mutex.try_lock() == false)
			return false;

		bool result = QueueBase<T, B>::dequeueTo(destination, count);
		_mutex.unlock();

		return result;
	}
}