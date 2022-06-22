#pragma once

namespace Utils
{
	template<typename T>
	MutexQueue<T>::MutexQueue(size_t size)
		: Queue(size)
		, _mutex()
	{
	}

	template<typename T>
	bool MutexQueue<T>::Enqueue(const Span<T> &buffer)
	{
		_mutex.Lock();
		bool result = Queue::Enqueue(buffer);
		_mutex.Unlock();

		return result;
	}

	template<typename T>	
	bool MutexQueue<T>::Enqueue(const T &element)
	{
		_mutex.Lock();
		bool result = Queue::Enqueue(element);
		_mutex.Unlock();

		return result;
	}

	template<typename T>
	size_t MutexQueue<T>::DequeueAllTo(T *destination)
	{
		_mutex.Lock();
		uint32_t result = Queue::DequeueAllTo(destination);
		_mutex.Unlock();

		return result;
	}

	template<typename T>
	size_t MutexQueue<T>::DequeueAllTo(Buffer<T> &destination)
	{
		_mutex.Lock();
		uint32_t result = Queue::DequeueAllTo(destination);
		_mutex.Unlock();

		return result;
	}

	template<typename T>
	bool MutexQueue<T>::DequeueTo(T *destination, size_t count)
	{
		_mutex.Lock();
		bool result = Queue::DequeueTo(destination, count);
		_mutex.Unlock();

		return result;
	}

	template<typename T>	
	bool MutexQueue<T>::TryEnqueue(const Span<T> &buffer)
	{
		bool result;

		if (_mutex.TryLock() == false)
			return false;

		result = Queue::Enqueue(buffer);
		_mutex.Unlock();

		return result;
	}

	template<typename T>
	bool MutexQueue<T>::TryEnqueue(const T &element)
	{
		bool result;

		if (_mutex.TryLock() == false)
			return false;

		result = Queue::Enqueue(element);
		_mutex.Unlock();

		return result;
	}

	template<typename T>
	bool MutexQueue<T>::TryDequeueAllTo(T *destination)
	{
		if (_mutex.TryLock() == false)
			return false;

		Queue::DequeueAllTo(destination);
		_mutex.Unlock();

		return true;
	}

	template<typename T>
	bool MutexQueue<T>::TryDequeueTo(T *destination, size_t count)
	{
		if (_mutex.TryLock() == false)
			return false;

		bool result = Queue::DequeueTo(destination, count);
		_mutex.Unlock();

		return result;
	}
}