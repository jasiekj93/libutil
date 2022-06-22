#pragma once

namespace util::stat
{
	template<typename T, size_t SIZE>
	MessageQueue<T, SIZE>::MessageQueue()
		: _objects()
		, _sizes()
	{
	}


	template<typename T, size_t SIZE>
	bool MessageQueue<T, SIZE>::enqueue(const T &element)
	{
		if (_sizes.isFull())
			return false;

		if (_objects.enqueue(element))
		{
			_sizes.enqueue(1);
			return true;
		}
		else
			return false;
	}

	template<typename T, size_t SIZE>
	bool MessageQueue<T, SIZE>::enqueue(const Span<T> & buffer)
	{
		if (_sizes.isFull())
			return false;

		if (_objects.enqueue(buffer))
		{
			_sizes.enqueue(buffer.size());
			return true;
		}
		else
			return false;
	}

	template<typename T, size_t SIZE>
	bool MessageQueue<T, SIZE>::dequeueTo(T *destination)
	{
		if (_sizes.isEmpty())
			return false;

		size_t size = _sizes.popFront();
		return _objects.dequeueTo(destination, size);
	}

	template<typename T, size_t SIZE>
	void MessageQueue<T, SIZE>::dequeue()
	{
		if (_sizes.isEmpty())
			return;

		size_t size = _sizes.popFront();
		_objects.dequeue(size);
	}

	template<typename T, size_t SIZE>
	size_t MessageQueue<T, SIZE>::dequeueAllTo(T *destination)
	{
		_sizes.clear();
		return _objects.dequeueAllTo(destination);
	}

	template<typename T, size_t SIZE>
	size_t MessageQueue<T, SIZE>::dequeueAll()
	{
		auto result = _objects.getCount();
		_sizes.clear();
		_objects.clear();
		return result;
	}
}