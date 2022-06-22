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
			if(this->size == span.size)
                return std::equal(this->data, this->data + this->size, span.data);
			else
				return false;
    }
}