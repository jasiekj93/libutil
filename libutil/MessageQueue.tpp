#pragma once

namespace util
{
	template<typename T, class B, class S>
	MessageQueueBase<T, B, S>::MessageQueueBase(size_t size)
		: _objects(size)
		, _sizes(size)
	{
	}


	template<typename T, class B, class S>
	bool MessageQueueBase<T, B, S>::enqueue(const T &element)
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

	template<typename T, class B, class S>
	bool MessageQueueBase<T, B, S>::enqueue(const Span<T>& buffer)
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

	template<typename T, class B, class S>
	bool MessageQueueBase<T, B, S>::dequeueTo(T *destination)
	{
		if (_sizes.isEmpty())
			return false;

		size_t size = _sizes.popFront();
		return _objects.dequeueTo(destination, size);
	}

	template<typename T, class B, class S>
	void MessageQueueBase<T, B, S>::dequeue()
	{
		if (_sizes.isEmpty())
			return;

		size_t size = _sizes.popFront();
		_objects.dequeue(size);
	}

	template<typename T, class B, class S>
	size_t MessageQueueBase<T, B, S>::dequeueAllTo(T *destination)
	{
		_sizes.clear();
		return _objects.dequeueAllTo(destination);
	}

	template<typename T, class B, class S>
	size_t MessageQueueBase<T, B, S>::dequeueAll()
	{
		auto result = _objects.count();
		_sizes.clear();
		_objects.clear();
		return result;
	}
}