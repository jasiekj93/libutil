#pragma once

namespace util::stat
{   
    template<typename T, size_t SIZE>
    Buffer<T, SIZE>::Buffer()
        : _count(0)

    {
    }
    template<typename T, size_t SIZE>
    Buffer<T, SIZE>::Buffer(const Span<T>& span)
    {
        add(span);
    }
        
    template<typename T, size_t SIZE>
    Buffer<T, SIZE>::Buffer(std::initializer_list<T> list)
    {
        add({ list.begin(), list.size() });
    }

    template<typename T, size_t SIZE>
    bool Buffer<T, SIZE>::add(const Span<T> &buffer)
    {
        if (buffer.data() == nullptr)
            return false;

        if ((_count + buffer.size()) > SIZE)
            return false;

        std::copy(buffer.begin(), buffer.end(), _data + _count);
        _count += buffer.size();

        return true;
    }

    template<typename T, size_t SIZE>
    bool Buffer<T, SIZE>::add(const T &object)
    {
        if (_count == SIZE)
            return false;

        _data[_count++] = object;
        return true;
    }

    template<typename T, size_t SIZE>
    bool Buffer<T, SIZE>::add(const T *pointer, size_t size) 
    { 
        return Add(Span<T>{ pointer, size }); 
    }

    template<typename T, size_t SIZE>
    void Buffer<T, SIZE>::deepClear()
    {
        for(size_t i = 0; i < SIZE; i++)
            _data[i] = T();
        _count = 0;
    }

    template<typename T, size_t SIZE>
    bool Buffer<T, SIZE>::shrink(size_t shrinkSize)
    {
        if (shrinkSize > _count)
            return false;

        _count -= shrinkSize;
        return true;
    }

    template<typename T, size_t SIZE>
    bool Buffer<T, SIZE>::shiftLeft(size_t startPosition, size_t size)
    {
        auto endPosition = startPosition + size;

        if (endPosition > _count)
            return false;

        std::copy(_data + endPosition, _data  + _count, _data + startPosition);

        _count -= size;
        return true;
    }

    template<typename T, size_t SIZE>
    bool Buffer<T, SIZE>::insert(size_t index, const Span<T> &span)
    {
        if((_count + span.size) > SIZE)
            return false;

        if (index > _count)
            return false;

        std::copy(_data + index, _data + _count, _data + index + span.size);
        std::copy(span.begin(), span.end(), _data + index);
        _count += span.size;

        return true;
    }

    template<typename T, size_t SIZE>
    bool Buffer<T, SIZE>::insert(size_t index, const T &object)
    {
        if(IsFull() == true)
            return false;

        if (index >= _count)
            return false;

        std::copy(_data + index, _data + _count, _data + index + 1);
        _data[index] = object;
        _count++;
        return true;
    }

    template<typename T, size_t SIZE>
    bool Buffer<T, SIZE>::insert(size_t index, const T *data, size_t size) 
    { 
        return Insert(index, Span<T>{ data, size }); 
    }

}