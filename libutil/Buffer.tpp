#pragma once

namespace util
{
	template<class T, class C>
	BufferBase<T, C>::BufferBase(size_t size)
		: _storage(size)
		, _count(0)
	{
	}

	template<class T, class C>
	BufferBase<T, C>::BufferBase(size_t size, const Span<T>& span)
		: BufferBase(size)
	{
		add(span);
	}

	template<class T, class C>
	BufferBase<T, C>::BufferBase(size_t size, std::initializer_list<T> list)
		: BufferBase(size)
	{
		add({ list.begin(), list.size() });
	}

	template<class T, class C>
	BufferBase<T, C>::BufferBase()
		: BufferBase(0)
	{
	}

	template<class T, class C>
	BufferBase<T, C>::BufferBase(const Span<T>& span)
		: BufferBase(span.size(), span)
	{
	}

	template<class T, class C>
	BufferBase<T, C>::BufferBase(std::initializer_list<T> list)
		: BufferBase(list.size(), list)
	{
	}


	template<class T, class C>
	bool BufferBase<T, C>::add(const Span<T> &buffer)
	{
		if (buffer.data() == nullptr)
			return false;

		if ((_count + buffer.size()) > _storage.size())
			return false;

		for (size_t i = 0; i < buffer.size(); i++)
			_storage[_count++] = buffer[i];

		return true;
	}

	template<class T, class C>
	bool BufferBase<T, C>::add(const T &object)
	{
		if (_count == _storage.size())
			return false;

		_storage[_count++] = object;
		return true;
	}

	template<class T, class C>
	bool BufferBase<T, C>::add(const T *pointer, size_t size) 
	{ 
		return add(Span<T>{ pointer, size }); 
	}

	template<class T, class C>
	void BufferBase<T, C>::deepClear()
	{
		for(size_t i = 0; i < _storage.size(); i++)
			_storage[i] = T();
		_count = 0;
	}

	template<class T, class C>
	bool BufferBase<T, C>::shrink(size_t shrinkSize)
	{
		if (shrinkSize > _count)
			return false;

		_count -= shrinkSize;
		return true;
	}

	template<class T, class C>
	bool BufferBase<T, C>::shiftLeft(size_t startPosition, size_t size)
	{
		auto endPosition = startPosition + size;

		if (endPosition > _count)
			return false;

        util::copy(data() + endPosition, 
            data() + _count, 
            data() + startPosition);

		_count -= size;
		return true;
	}

	template<class T, class C>
	bool BufferBase<T, C>::insert(size_t index, const Span<T> &span)
	{
		if((_count + span.size()) > _storage.size())
			return false;

		if (index > _count)
			return false;

        util::copy(data() + index, 
            data() + _count, 
            data() + index + span.size());

        util::copy(span.begin(), span.end(), data() + index);
		_count += span.size();

		return true;
	}

	template<class T, class C>
	bool BufferBase<T, C>::insert(size_t index, const T &object)
	{
		if(isFull())
			return false;

		if (index >= _count)
			return false;

        util::copy(data() + index, 
            data() + _count,
            data() + index + 1);
		_storage[index] = object;
		_count++;
		return true;
	}

	template<class T, class C>
	bool BufferBase<T, C>::insert(size_t index, const T *data, size_t size) 
	{ 
		return insert(index, Span<T>{ data, size }); 
	}

    template<class T, class C>
    bool BufferBase<T, C>::operator==(const BufferBase& buffer) const
    {
        if(_count != buffer._count)
            return false;

        return std::equal(cbegin(), cbegin() + _count, buffer.cbegin());
    }
}