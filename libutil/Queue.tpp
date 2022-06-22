#pragma once

namespace util
{
	template<typename T>
	Queue<T>::Queue(size_t size)
		: _buffer(size)
	{
	}

	template<typename T>
	size_t Queue<T>::dequeueAllTo(T *destination)
	{
		size_t result = _buffer.Count();
		if (this->dequeueTo(destination, _buffer.count()))
			return result;
		else
			return UINT32_MAX;
	}

	template<typename T>
	size_t Queue<T>::dequeueAllTo(Buffer<T> &destination)
	{
		size_t size = _buffer.count();
		bool result = destination.add({_buffer.data(), size});
		_buffer.clear();
		if (result == true)
			return size;
		else
			return UINT32_MAX;
	}

	template<typename T>
	size_t Queue<T>::dequeueAll()
	{
		size_t result = _buffer.count();
		this->dequeue(_buffer.count());
		return result;
	}

	template<typename T>
	bool Queue<T>::dequeueTo(T *destination, size_t count)
	{
		if (count > _buffer.count())
			return false;

		if (destination == nullptr)
			return false;

        copy<T>(destination, _buffer.data(), count);
		_buffer.ShiftLeft(0, count);

		return true;
	}

	template<typename T>
	T Queue<T>::popBack()
	{
		auto result = back();
		_buffer.shrink(1);
		return result;
	}

	template<typename T>
	T Queue<T>::popFront()
	{
		auto result = front();
		_buffer.shiftLeft(0, 1);
		return result;
	}
}