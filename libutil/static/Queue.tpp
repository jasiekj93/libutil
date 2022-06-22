#pragma once

namespace Utils::Static
{
	template<typename T, size_t SIZE>
	Queue<T, SIZE>::Queue()
		: _buffer()
	{
	}

	template<typename T, size_t SIZE>
	size_t Queue<T, SIZE>::DequeueAllTo(T *destination)
	{
		size_t result = _buffer.Count();
		if (this->DequeueTo(destination, _buffer.Count()))
			return result;
		else
			return UINT32_MAX;
	}

	template<typename T, size_t SIZE>
	size_t Queue<T, SIZE>::DequeueAllTo(Buffer<T, SIZE> &destination)
	{
		size_t size = _buffer.Count();
		bool result = destination.Add({_buffer.Data(), size});
		_buffer.Clear();
		if (result == true)
			return size;
		else
			return UINT32_MAX;
	}

	template<typename T, size_t SIZE>
	size_t Queue<T, SIZE>::DequeueAll()
	{
		size_t result = _buffer.Count();
		this->Dequeue(_buffer.Count());
		return result;
	}

	template<typename T, size_t SIZE>	
	bool Queue<T, SIZE>::DequeueTo(T *destination, size_t count)
	{
		if (count > _buffer.Count())
			return false;

		if (destination == nullptr)
			return false;

		std::memcpy(destination, _buffer.Data(), count);
		_buffer.ShiftLeft(0, count);

		return true;
	}

	template<typename T, size_t SIZE>
	T Queue<T, SIZE>::PopBack()
	{
		auto result = Back();
		_buffer.Shrink(1);
		return result;
	}

	template<typename T, size_t SIZE>
	T Queue<T, SIZE>::PopFront()
	{
		auto result = Front();
		_buffer.ShiftLeft(0, 1);
		return result;
	}

	template<typename T, size_t SIZE>
	hword Queue<T, SIZE>::GetUint16(size_t index) const
	{
		if ((index + 1) >= _buffer.Count())
			return UINT16_MAX;

		return ((uint16_t)_buffer[index] << 8) |
			(uint16_t)_buffer[index + 1];
	}

	template<typename T, size_t SIZE>
	word Queue<T, SIZE>::GetUint32(size_t index) const
	{
		if ((index + 3) >= _buffer.Count())
			return WORD_MAX;
		else
			return BytesToWord(&_buffer[index]);
	}
}