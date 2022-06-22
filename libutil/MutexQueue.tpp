#pragma once

namespace util
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
		_mutex.lock();
		auto result = Queue::enqueue(buffer);
		_mutex.unlock();

		return result;
	}

	template<typename T>	
	bool MutexQueue<T>::enqueue(const T &element)
	{
		_mutex.lock();
		auto result = Queue::enqueue(element);
		_mutex.unlock();

		return result;
	}

	template<typename T>
	size_t MutexQueue<T>::dequeueAllTo(T *destination)
	{
		_mutex.lock();
		auto result = Queue::dequeueAllTo(destination);
		_mutex.unlock();

		return result;
	}

	template<typename T>
	size_t MutexQueue<T>::dequeueAllTo(Buffer<T> &destination)
	{
		_mutex.lock();
		auto result = Queue::dequeueAllTo(destination);
		_mutex.unlock();

		return result;
	}

	template<typename T>
	bool MutexQueue<T>::dequeueTo(T *destination, size_t count)
	{
		_mutex.lock();
		bool result = Queue::dequeueTo(destination, count);
		_mutex.unlock();

		return result;
	}

	template<typename T>	
	bool MutexQueue<T>::tryEnqueue(const Span<T> &buffer)
	{
		bool result;

		if (_mutex.try_lock() == false)
			return false;

		result = Queue::enqueue(buffer);
		_mutex.unlock();

		return result;
	}

	template<typename T>
	bool MutexQueue<T>::tryEnqueue(const T &element)
	{
		bool result;

		if (_mutex.try_lock() == false)
			return false;

		result = Queue::enqueue(element);
		_mutex.unlock();

		return result;
	}

	template<typename T>
	bool MutexQueue<T>::tryDequeueAllTo(T *destination)
	{
		if (_mutex.try_lock() == false)
			return false;

		Queue::dequeueAllTo(destination);
		_mutex.unlock();

		return true;
	}

	template<typename T>
	bool MutexQueue<T>::tryDequeueTo(T *destination, size_t count)
	{
		if (_mutex.try_lock() == false)
			return false;

		bool result = Queue::dequeueTo(destination, count);
		_mutex.unlock();

		return result;
	}
}