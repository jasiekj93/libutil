#pragma once

#include <cstddef>
#include <memory>
#include <libutil/Span.hpp>
#include <libutil/Copy.hpp>

namespace util
{
    template<class T>
    class DynArray
    {
    public:
        DynArray(size_t);
        DynArray(size_t, std::initializer_list<T>);
        DynArray(size_t, const T*);
        DynArray(size_t, const Span<T>&);
        DynArray(const DynArray&);

        DynArray& operator=(const DynArray&);
        bool operator==(const DynArray&) const;
        constexpr bool operator!=(const DynArray& a) const { return !(*this == a); } 

        constexpr T& at(size_t i) { return _data[i]; }
        constexpr const T& at(size_t i) const { return _data[i]; }
        constexpr T& operator[](size_t i) { return _data[i]; }
        constexpr const T& operator[](size_t i) const { return _data[i]; }
        constexpr T& front() { return _data[0]; }
        constexpr const T& front() const { return _data[0]; }
        constexpr T& back() { return _data[_size - 1]; }
        constexpr const T& back() const { return _data[_size - 1]; }
        constexpr T* data() { return _data.get(); }
        constexpr const T* data() const { return _data.get(); }

        constexpr T* begin() { return _data.get(); }
        constexpr const T* begin() const { return _data.get(); }
        constexpr const T* cbegin() const { return _data.get(); }
        constexpr T* end() { return _data.get() + _size; }
        constexpr const T* end() const { return _data.get() + _size; }
        constexpr const T* cend() const { return _data.get() + _size; }
        constexpr T* rbegin() { return _data.get() + _size - 1; }
        constexpr const T* crbegin() const { return _data.get() + _size - 1; }
        constexpr T* rend() { return _data.get() - 1; }
        constexpr const T* crend() const { return _data.get() - 1; }

        constexpr bool empty() const { return (_size == 0); }
        constexpr size_t size() const { return _size; }
        constexpr size_t max_size() const { return _size; }

        constexpr void fill(const T& val) { std::fill(begin(), end(), val); }
        constexpr void swap(DynArray& arr) { std::swap(_data, arr._data); std::swap(_size, arr._size); }

        constexpr Span<T> toSpan() const { return { data(), size() }; }   

    private:
        std::unique_ptr<T[]> _data;
        size_t _size;
    };

    template<class T, size_t SIZE>
    class Array
    {
    public:
        explicit Array(size_t = 0);
        Array(std::initializer_list<T>);
        Array(const T*);
        Array(const Span<T>&);
        Array(const Array&);

        Array& operator=(const Array&);
        bool operator==(const Array&) const;
        constexpr bool operator!=(const Array& a) const { return !(*this == a); }

        constexpr T& at(size_t i) { return _data[i]; }
        constexpr const T& at(size_t i) const { return _data[i]; }
        constexpr T& operator[](size_t i) { return _data[i]; }
        constexpr const T& operator[](size_t i) const { return _data[i]; }
        constexpr T& front() { return _data[0]; }
        constexpr const T& front() const { return _data[0]; }
        constexpr T& back() { return _data[SIZE - 1]; }
        constexpr const T& back() const { return _data[SIZE - 1]; }
        constexpr T* data() { return _data; }
        constexpr const T* data() const { return _data; }

        constexpr T* begin() { return _data; }
        constexpr const T* begin() const { return _data; }
        constexpr const T* cbegin() const { return _data; }
        constexpr T* end() { return _data + SIZE; }
        constexpr const T* end() const { return _data + SIZE; }
        constexpr const T* cend() const { return _data + SIZE; }
        constexpr T* rbegin() { return _data + SIZE - 1; }
        constexpr const T* crbegin() const { return _data + SIZE - 1; }
        constexpr T* rend() { return _data - 1; }
        constexpr const T* crend() const { return _data - 1; }

        constexpr bool empty() const { return (SIZE == 0); }
        constexpr size_t size() const { return SIZE; }
        constexpr size_t max_size() const { return SIZE; }

        constexpr void fill(const T& val) { std::fill(begin(), end(), val); }
        constexpr void swap(Array& arr) { std::swap(_data, arr._data); }

        constexpr Span<T> toSpan() const { return { data(), size() }; }   
        
    private:
        T _data[SIZE];
    };
}

#include <libutil/Array.tpp>