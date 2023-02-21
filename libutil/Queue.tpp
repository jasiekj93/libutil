#pragma once

namespace util
{
	template<typename T, class B>
	QueueBase<T, B>::QueueBase(size_t size)
		: _buffer(size)
	{
	}

	template<typename T, class B>
	size_t QueueBase<T, B>::dequeueAllTo(T *destination)
	{
		size_t result = _buffer.count();
		if (this->dequeueTo(destination, _buffer.count()))
			return result;
		else
			return UINT32_MAX;
	}

	template<typename T, class B>
	size_t QueueBase<T, B>::dequeueAllTo(B &destination)
	{
		size_t size = _buffer.count();
		bool result = destination.add({_buffer.data(), size});
		_buffer.clear();
		if (result == true)
			return size;
		else
			return UINT32_MAX;
	}

	template<typename T, class B>
	size_t QueueBase<T, B>::dequeueAll()
	{
		size_t result = _buffer.count();
		this->dequeue(_buffer.count());
		return result;
	}

	template<typename T, class B>
	bool QueueBase<T, B>::dequeueTo(T *destination, size_t count)
	{
		if (count > _buffer.count())
			return false;

		if (destination == nullptr)
			return false;

        util::copy(_buffer.begin(), _buffer.begin() + count, destination);
		_buffer.shiftLeft(0, count);

		return true;
	}

	template<typename T, class B>
	T QueueBase<T, B>::popBack()
	{
		auto result = back();
		_buffer.shrink(1);
		return result;
	}

	template<typename T, class B>
	T QueueBase<T, B>::popFront()
	{
		auto result = front();
		_buffer.shiftLeft(0, 1);
		return result;
	}
}