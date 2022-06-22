#pragma once

namespace util
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
		if (buffer.data() == nullptr)
			return false;

		if ((_count + buffer.size()) > _size)
			return false;

		for (size_t i = 0; i < buffer.size(); i++)
			_data[_count++] = buffer[i];

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

        std::copy(_data.get() + endPosition, 
            _data.get() + _count, 
            _data.get() + startPosition);

		_count -= size;
		return true;
	}

	template<typename T>
	bool Buffer<T>::insert(size_t index, const Span<T> &span)
	{
		if((_count + span.size()) > _size)
			return false;

		if (index > _count)
			return false;

        std::copy(_data.get() + index, 
            _data.get() + _count, 
            _data.get() + index + span.size());

        std::copy(span.begin(), span.end(), _data.get() + index);
		_count += span.size();

		return true;
	}

	template<typename T>
	bool Buffer<T>::insert(size_t index, const T &object)
	{
		if(isFull())
			return false;

		if (index >= _count)
			return false;

        std::copy(_data.get() + index, 
            _data.get() + _count, 
            _data.get() + index + 1);
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