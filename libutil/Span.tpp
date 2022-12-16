#pragma once

namespace util
{
    template<class T>
    Span<T>::Span(const T* data, size_t size)
        : _data(data)
        , _size(size)
    {
    }

    template<class T> 
    bool Span<T>::operator==(const Span<T> &span)
    {
			if(this->_size == span._size)
                return std::equal(this->_data, this->_data + this->_size, span._data);
			else
				return false;
    }
}