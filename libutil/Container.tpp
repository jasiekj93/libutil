#pragma once

namespace util
{
    template<class T>
    inline DynamicContainer<T>::DynamicContainer(size_t size)
        : _data(std::make_unique<T[]>(size))
        , _size(size)
    {
    }

    template<class T>
    DynamicContainer<T>& DynamicContainer<T>::operator=(const DynamicContainer& c)
    {
        _data.reset(std::make_unique<T[]>(c.size()));
        _size = c.size();

        std::copy(c.cbegin(), c.cend(), this->begin());
    }

    template<class T>
    bool DynamicContainer<T>::operator==(const DynamicContainer& c)
    {
        return std::equal(c.cbegin(), c.cend(), this->begin());
    }


    template<class T, size_t SIZE>
    inline StaticContainer<T, SIZE>::StaticContainer(size_t size)
    {
    }

    template<class T, size_t SIZE>
    StaticContainer<T, SIZE>& StaticContainer<T, SIZE>::operator=(const StaticContainer& c)
    {
        std::copy(c.cbegin(), c.cend(), this->begin());
    }

    template<class T, size_t SIZE>
    bool StaticContainer<T, SIZE>::operator==(const StaticContainer& c)
    {
        return std::equal(c.cbegin(), c.cend(), this->begin());
    }
}