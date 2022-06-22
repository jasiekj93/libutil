#pragma once

namespace util
{
    template<class T>
        DynArray<T>::DynArray(size_t size)
            : _data(std::make_unique<T[]>(size))
            , _size(size)
        {
        }

    template<class T>
        DynArray<T>::DynArray(size_t size, std::initializer_list<T> list)
            : DynArray(size)
        {
            std::copy(list.begin(), list.end(), _data.get());
        }

    template<class T>
        DynArray<T>::DynArray(size_t size, const T* pointer)
            : DynArray(size)
        {
            std::copy(pointer, pointer + size, _data.get());
        }

    template<class T>
        DynArray<T>::DynArray(const DynArray& arr)
            : DynArray(arr._size)
        {
            std::copy(arr.cbegin(), arr.cend(), _data.get());
        }
    
    template<class T>
        DynArray<T>& DynArray<T>::operator=(const DynArray& arr)
        {
            _data.
        }
}