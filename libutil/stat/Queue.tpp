#pragma once

namespace util::stat
{
	template<typename T, size_t SIZE>
	Queue<T, SIZE>::Queue()
		: _buffer()
	{
	}

	template<typename T, size_t SIZE>
	size_t Queue<T, SIZE>::dequeueAllTo(T *destination)
	{
		size_t result = _buffer.count();
		if (this->dequeueTo(destination, _buffer.count()))
			return result;
		else
			return UINT32_MAX;
	}

	template<typename T, size_t SIZE>
	size_t Queue<T, SIZE>::dequeueAllTo(Buffer<T, SIZE> &destination)
	{
		size_t size = _buffer.count();
		bool result = destination.add(_buffer.toSpan());
		_buffer.Clear();
		if (result == true)
			return size;
		else
			return UINT32_MAX;
	}

	template<typename T, size_t SIZE>
	size_t Queue<T, SIZE>::dequeueAll()
	{
		size_t result = _buffer.count();
		this->dequeue(_buffer.count());
		return result;
	}

	template<typename T, size_t SIZE>	
	bool Queue<T, SIZE>::dequeueTo(T *destination, size_t count)
	{
		if (count > _buffer.count())
			return false;

		if (destination == nullptr)
			return false;

		std::memcpy(destination, _buffer.data(), count);
		_buffer.shiftLeft(0, count);

		return true;
	}

	template<typename T, size_t SIZE>
	T Queue<T, SIZE>::popBack()
	{
		auto result = back();
		_buffer.shrink(1);
		return result;
	}

	template<typename T, size_t SIZE>
	T Queue<T, SIZE>::popFront()
	{
		auto result = front();
		_buffer.shiftLeft(0, 1);
		return result;
	}
}