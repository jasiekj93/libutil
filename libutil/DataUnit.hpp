#pragma once

/**
 * @file DataUnit.hpp
 * @author Adrian Szczepanski
 * @date 24-09-2021
 * @brief 
 * @details
 */

#include <cstdint>
#include <cstddef>
#include <cstring>
#include <array>
#include <algorithm>

namespace util
{
    using byte = uint8_t;
    using hword = uint16_t;
    using word = uint32_t;
    using dword = uint64_t;

    static constexpr byte BYTE_MAX = UINT8_MAX;
    static constexpr hword HWORD_MAX = UINT16_MAX;
    static constexpr word WORD_MAX = UINT32_MAX;
    static constexpr dword DWORD_MAX = UINT64_MAX;

    template<class T>
    inline std::array<byte, sizeof(T)> toBytes(const T &object)
    {
        std::array<byte, sizeof(T)> result;
        std::memcpy(result.data(), &object, sizeof(T));
        return result;
    }

    template<class T>
    inline void toBytes(byte *out, const T &object)
    {
        std::memcpy(out, &object, sizeof(T));
    }

    template<class T>
    inline std::array<byte, sizeof(T)> toBytesReversed(const T &object)
    {
        std::array<byte, sizeof(T)> result;
        std::memcpy(result.data(), &object, sizeof(T));
        std::reverse(result.begin(), result.end());

        return result;
    }

    template<class T>
    inline void toBytesReversed(byte *out, const T &object)
    {
        std::memcpy(out, &object, sizeof(T));
        std::reverse(out, out + sizeof(T));
    }

    template<class T>
    inline T fromBytes(const byte *buffer)
    {
        T result;
        std::memcpy(&result, buffer, sizeof(T));
        return result;
    }

    template<class T>
    inline T fromBytes(const std::array<byte, sizeof(T)> &buffer)
    {
        T result;
        std::memcpy(&result, buffer.data(), sizeof(T));
        return result;
    }
    
    template<class T>
    inline T fromBytesReversed(const byte *buffer)
    {
        T result;
        auto pointer = (byte *)&result;
        std::memcpy(pointer, buffer, sizeof(T));
        std::reverse(pointer, pointer + sizeof(T));
        return result;
    }

    template<class T>
    inline T fromBytesReversed(const std::array<byte, sizeof(T)> &buffer)
    {
        T result;
        auto pointer = (byte *)&result;
        std::memcpy(pointer, buffer.data(), sizeof(T));
        std::reverse(pointer, pointer + sizeof(T));
        return result;
    }
    
    inline auto bytesToHword(const byte *b) { return fromBytesReversed<hword>(b); }
    inline auto bytesToHword(const std::array<byte, sizeof(hword)> &b) { return fromBytesReversed<hword>(b); }
    inline auto bytesToWord(const byte *b) { return fromBytesReversed<word>(b); }
    inline auto bytesToWord(const std::array<byte, sizeof(word)> &b) { return fromBytesReversed<word>(b); }
    inline auto bytesToDword(const byte *b) { return fromBytesReversed<dword>(b); }
    inline auto bytesToDword(const std::array<byte, sizeof(dword)> &b) { return fromBytesReversed<dword>(b); }

    inline auto hwordToBytes(hword v) { return toBytesReversed<hword>(v); }
    inline auto hwordToBytes(byte *b, hword v) { return toBytesReversed<hword>(b, v); }
    inline auto wordToBytes(word v) { return toBytesReversed<word>(v); }
    inline auto wordToBytes(byte *b, word v) { return toBytesReversed<word>(b, v); }
    inline auto dwordToBytes(dword v) { return toBytesReversed<dword>(v); }
    inline auto dwordToBytes(byte *b, dword v) { return toBytesReversed<dword>(b, v); }
}