#pragma once

#include <cstddef>
#include <memory>

namespace util
{
    template<class T>
    class DynamicContainer
    {
    public:
        DynamicContainer(size_t);

        constexpr T* data() { return _data.get(); }
        constexpr const T* data() const { return _data.get(); }

        constexpr size_t size() const { return _size; }

        constexpr T* begin() { return _data.get(); }
        constexpr const T* cbegin() const { return _data.get(); }
        constexpr T* end() { return _data.get() + _size; }
        constexpr const T* cend() const { return _data.get() + _size; }
        constexpr T* rbegin() { return _data.get() + _size - 1; }
        constexpr const T* crbegin() const { return _data.get() + _size - 1; }
        constexpr T* rend() { return _data.get() - 1; }
        constexpr const T* crend() const { return _data.get() - 1; }

        constexpr T& operator[](size_t i) { return _data[i]; }
        constexpr const T& operator[](size_t i) const { return _data[i]; }

        DynamicContainer& operator=(const DynamicContainer&);
        bool operator==(const DynamicContainer&);

    private:
        std::unique_ptr<T[]> _data;
        size_t _size;
    };

    template<class T, size_t SIZE>
    class StaticContainer
    {
    public:
        StaticContainer(size_t);

        constexpr T* data() { return _data; }
        constexpr const T* data() const { return _data; }

        constexpr size_t size() const { return SIZE; }

        constexpr T* begin() { return _data; }
        constexpr const T* cbegin() const { return _data; }
        constexpr T* end() { return _data + SIZE; }
        constexpr const T* cend() const { return _data + SIZE; }
        constexpr T* rbegin() { return _data + SIZE - 1; }
        constexpr const T* crbegin() const { return _data + SIZE - 1; }
        constexpr T* rend() { return _data - 1; }
        constexpr const T* crend() const { return _data - 1; }

        constexpr T& operator[](size_t i) { return _data[i]; }
        constexpr const T& operator[](size_t i) const { return _data[i]; }

        StaticContainer& operator=(const StaticContainer&);
        bool operator==(const StaticContainer&);

    private:
        T _data[SIZE];
    };
}

#include <libutil/Container.tpp>