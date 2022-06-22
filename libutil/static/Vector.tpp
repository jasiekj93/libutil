#pragma once

#include <cstring>

namespace Utils::Static
{
    template<size_t SIZE>
    Vector<SIZE>::Vector()
        : _count(0)
    {
    }

    template<size_t SIZE>
    Vector<SIZE>::Vector(const ByteSpan &span)
        : Vector()
    {
        if(span.size <= SIZE)
        {
            std::memcpy(_data, span.data, span.size);
            _count = span.size;
        }
    }

    template<size_t SIZE>
    Vector<SIZE>::Vector(std::initializer_list<byte> list)
        : Vector()
    {
        if(list.size() <= SIZE)
        {
            std::memcpy(_data, list.begin(), list.size());
            _count = list.size();
        }
    }

    template<size_t SIZE>
    bool Vector<SIZE>::Put(byte object)
    {
        if(_count == SIZE)
            return false;

        _data[_count++] = object;
        return true;
    }
    
    template<size_t SIZE>
    bool Vector<SIZE>::Append(const ByteSpan &span)
    {
        if((_count + span.size) > SIZE)
            return false;

        std::memcpy(&_data[_count], span.data, span.size);
        _count += span.size;
        return true;
    }

    template<size_t SIZE>
    bool Vector<SIZE>::operator==(const Vector<SIZE> &vector) const
    {
        if(this->_count == vector._count)
            return (std::memcmp(this->_data, vector._data, this->_count) == 0);
        else
            return false;
    }

    template<size_t SIZE>
    bool Vector<SIZE>::operator!=(const Vector<SIZE> &vector) const
    {
        return ((*this == vector) == false);
    }
}