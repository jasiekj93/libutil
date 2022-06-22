#pragma once

#include <libutil/Span.hpp>
#include <memory>
#include <algorithm>

namespace util
{
    template<typename T, size_t N>
    class Array : public std::array<T, N>
    {
    public:
        using std::array<T, N>::array;

        inline Span<T> toSpan() const { return { this->data(), this->size() }; }   
    };

    template<class T>
    class DynArray
    {
    public:
        explicit DynArray(size_t);
        DynArray(size_t, std::initializer_list<T>);
        DynArray(size_t, const T*);
        DynArray(size_t, const Span<T>&);
        DynArray(const DynArray&);

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
        constexpr const T* cbegin() const { return _data.get(); }
        constexpr T* end() { return _data.get() + _size; }
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

        Span<T> toSpan() const { return { data(), size() }; }   

        DynArray& operator=(const DynArray&);
        bool operator==(const DynArray&) const;

    private:
        std::unique_ptr<T[]> _data;
        size_t _size;
    };

    template<size_t N>
    using ByteArray = Array<byte, N>;
    template<size_t N>
    using HwordArray = Array<hword, N>;
    template<size_t N>
    using WordArray = Array<word, N>;
    template<size_t N>
    using DwordArray = Array<dword, N>;

    using ByteDynArray = DynArray<byte>;
    using HwordDynArray = DynArray<hword>;
    using WordDynArray = DynArray<word>;
    using DwordDynArray = DynArray<dword>;
}

#include <libutil/Array.tpp>