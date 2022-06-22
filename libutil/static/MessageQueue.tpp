#pragma once

namespace Utils::Static
{
	template<typename T, size_t SIZE>
	MessageQueue<T, SIZE>::MessageQueue()
		: _objects()
		, _sizes()
	{
	}


	template<typename T, size_t SIZE>
	bool MessageQueue<T, SIZE>::Enqueue(const T &element)
	{
		if (_sizes.IsFull())
			return false;

		if (_objects.Enqueue(element))
		{
			_sizes.Enqueue(1);
			return true;
		}
		else
			return false;
	}

	template<typename T, size_t SIZE>
	bool MessageQueue<T, SIZE>::Enqueue(const Span<T> & buffer)
	{
		if (_sizes.IsFull())
			return false;

		if (_objects.Enqueue(buffer))
		{
			_sizes.Enqueue(buffer.size);
			return true;
		}
		else
			return false;
	}

	template<typename T, size_t SIZE>
	bool MessageQueue<T, SIZE>::DequeueTo(T *destination)
	{
		if (_sizes.IsEmpty())
			return false;

		size_t size = _sizes.PopFront();
		return _objects.DequeueTo(destination, size);
	}

	template<typename T, size_t SIZE>
	void MessageQueue<T, SIZE>::Dequeue()
	{
		if (_sizes.IsEmpty())
			return;

		size_t size = _sizes.PopFront();
		_objects.Dequeue(size);
	}

	template<typename T, size_t SIZE>
	uint32_t MessageQueue<T, SIZE>::DequeueAllTo(T *destination)
	{
		_sizes.Clear();
		return _objects.DequeueAllTo(destination);
	}

	template<typename T, size_t SIZE>
	uint32_t MessageQueue<T, SIZE>::DequeueAll()
	{
		auto result = _objects.GetCount();
		_sizes.Clear();
		_objects.Clear();
		return result;
	}
}