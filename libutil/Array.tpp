#pragma once

namespace util
{
    template<class T>
    inline DynArray<T>::DynArray(size_t size)
        : _data(std::make_unique<T[]>(size))
        , _size(size)
    {
    }

template<class T>
    DynArray<T>::DynArray(size_t size, std::initializer_list<T> list)
        : DynArray(size)
    {
        util::copy(list.begin(), list.end(), _data.get());
    }

    template<class T>
    DynArray<T>::DynArray(size_t size, const T* pointer)
        : DynArray(size)
    {
        util::copy(pointer, pointer + size, _data.get());
    }

    template<class T>
    DynArray<T>::DynArray(const DynArray& arr)
        : DynArray(arr._size)
    {
        util::copy(arr.cbegin(), arr.cend(), _data.get());
    }

    template<class T>
    DynArray<T>& DynArray<T>::operator=(const DynArray& c)
    {
        _data.reset(new T[c.size()]);
        _size = c.size();

        util::copy(c.cbegin(), c.cend(), this->begin());
        return *this;
    }

    template<class T>
    bool DynArray<T>::operator==(const DynArray& c) const
    {
        return std::equal(c.cbegin(), c.cend(), this->cbegin());
    }


    template<class T, size_t SIZE>
    inline Array<T, SIZE>::Array(size_t size)
    {
    }

    template<class T, size_t SIZE>
    inline Array<T, SIZE>::Array(std::initializer_list<T> list)
    {
        util::copy(list.begin(), list.end(), _data);
    }

    template<class T, size_t SIZE>
    inline Array<T, SIZE>::Array(const T* pointer)
    {
        util::copy(pointer, pointer + SIZE, _data);
    }

    template<class T, size_t SIZE>
    inline Array<T, SIZE>::Array(const Span<T>& span)
    {
        util::copy(span.begin(), span.end(), _data);
    }

    template<class T, size_t SIZE>
    Array<T, SIZE>::Array(const Array& arr)
    {
        util::copy(arr.cbegin(), arr.cend(), _data);
    }

    template<class T, size_t SIZE>
    Array<T, SIZE>& Array<T, SIZE>::operator=(const Array& c)
    {
        util::copy(c.cbegin(), c.cend(), this->begin());
        return *this;
    }

    template<class T, size_t SIZE>
    bool Array<T, SIZE>::operator==(const Array& c) const
    {
        return std::equal(c.cbegin(), c.cend(), this->cbegin());
    }
}