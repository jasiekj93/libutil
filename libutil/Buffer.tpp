#pragma once
#include <libutil/Copy.hpp>

namespace Utils
{
	template<typename T>
	Buffer<T>::Buffer(size_t size)
		: _size(size)
		, _data(std::make_unique<T[]>(size))
		, _count(0)

	{
	}

	template<typename T>
	bool Buffer<T>::add(const Span<T> &buffer)
	{
		if (buffer.data == nullptr)
			return false;

		if ((_count + buffer.size) > _size)
			return false;

		for (size_t i = 0; i < buffer.size; i++)
			_data[_count++] = buffer.data[i];

		return true;
	}

	template<typename T>
	bool Buffer<T>::add(const T &object)
	{
		if (_count == _size)
			return false;

		_data[_count++] = object;
		return true;
	}

	template<typename T>
	bool Buffer<T>::add(const T *pointer, size_t size) 
	{ 
		return add(Span<T>{ pointer, size }); 
	}

	template<typename T>
	void Buffer<T>::deepClear()
	{
		for(size_t i = 0; i < _size; i++)
			_data[i] = T();
		_count = 0;
	}

	template<typename T>
	bool Buffer<T>::shrink(size_t shrinkSize)
	{
		if (shrinkSize > _count)
			return false;

		_count -= shrinkSize;
		return true;
	}

	template<typename T>
	bool Buffer<T>::shiftLeft(size_t startPosition, size_t size)
	{
		auto endPosition = startPosition + size;

		if (endPosition > _count)
			return false;

        move<T>(&_data[startPosition], &_data[endPosition], _count - endPosition);

		_count -= size;
		return true;
	}

	template<typename T>
	bool Buffer<T>::insert(size_t index, const Span<T> &span)
	{
		if((_count + span.size) > _size)
			return false;

		if (index > _count)
			return false;

		move<T>(&_data[index + span.size], &_data[index], _count - index);	
		copy<T>(&_data[index], span.data, span.size);
		_count += span.size;

		return true;
	}

	template<typename T>
	bool Buffer<T>::insert(size_t index, const T &object)
	{
		if(isFull() == true)
			return false;

		if (index >= _count)
			return false;

		move<T>(&_data[index+1], &_data[index], _count - index);	
		_data[index] = object;
		_count++;
		return true;
	}

	template<typename T>
	bool Buffer<T>::insert(size_t index, const T *data, size_t size) 
	{ 
		return insert(index, ByteSpan{ data, size }); 
	}
}