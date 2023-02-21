#pragma once

/**
 * @file DataUnit.hpp
 * @author Adrian Szczepanski
 * @date 24-09-2021
 * @brief 
 * @details
 */

#include <cstdint>
#include <cstring>
#include <libutil/Array.hpp>
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

    template<size_t S>
    using ByteArray = Array<byte, S>;
    template<size_t S>
    using HwordArray = Array<hword, S>;
    template<size_t S>
    using WordArray = Array<word, S>;
    template<size_t S>
    using DwordArray = Array<dword, S>;

	using ByteSpan = Span<byte>;
	using HwordSpan = Span<hword>;
	using WordSpan = Span<word>;
	using DwordSpan = Span<dword>;

    template<class T>
    inline ByteArray<sizeof(T)> toBytes(const T &object)
    {
        ByteArray<sizeof(T)> result;
        util::memcpy(result.data(), &object, sizeof(T));
        return result;
    }

    template<class T>
    inline void toBytes(byte *out, const T &object)
    {
        util::memcpy(out, &object, sizeof(T));
    }

    template<class T>
    inline ByteArray<sizeof(T)> toBytesReversed(const T &object)
    {
        ByteArray<sizeof(T)> result;
        util::memcpy(result.data(), &object, sizeof(T));
        util::reverse(result.begin(), result.end());

        return result;
    }

    template<class T>
    inline void toBytesReversed(byte *out, const T &object)
    {
        util::memcpy(out, &object, sizeof(T));
        util::reverse(out, out + sizeof(T));
    }

    template<class T>
    inline T fromBytes(const byte *buffer)
    {
        T result;
        util::memcpy(&result, buffer, sizeof(T));
        return result;
    }

    template<class T>
    inline T fromBytes(const ByteArray<sizeof(T)> &buffer)
    {
        T result;
        util::memcpy(&result, buffer.data(), sizeof(T));
        return result;
    }
    
    template<class T>
    inline T fromBytesReversed(const byte *buffer)
    {
        T result;
        auto pointer = (byte *)&result;
        util::memcpy(pointer, buffer, sizeof(T));
        util::reverse(pointer, pointer + sizeof(T));
        return result;
    }

    template<class T>
    inline T fromBytesReversed(const ByteArray<sizeof(T)> &buffer)
    {
        T result;
        auto pointer = (byte *)&result;
        util::memcpy(pointer, buffer.data(), sizeof(T));
        util::reverse(pointer, pointer + sizeof(T));
        return result;
    }
    
    inline auto bytesToHword(const byte *b) { return fromBytesReversed<hword>(b); }
    inline auto bytesToHword(const ByteArray<sizeof(hword)> &b) { return fromBytesReversed<hword>(b); }
    inline auto bytesToWord(const byte *b) { return fromBytesReversed<word>(b); }
    inline auto bytesToWord(const ByteArray<sizeof(word)> &b) { return fromBytesReversed<word>(b); }
    inline auto bytesToDword(const byte *b) { return fromBytesReversed<dword>(b); }
    inline auto bytesToDword(const ByteArray<sizeof(dword)> &b) { return fromBytesReversed<dword>(b); }

    inline auto hwordToBytes(hword v) { return toBytesReversed<hword>(v); }
    inline auto hwordToBytes(byte *b, hword v) { return toBytesReversed<hword>(b, v); }
    inline auto wordToBytes(word v) { return toBytesReversed<word>(v); }
    inline auto wordToBytes(byte *b, word v) { return toBytesReversed<word>(b, v); }
    inline auto dwordToBytes(dword v) { return toBytesReversed<dword>(v); }
    inline auto dwordToBytes(byte *b, dword v) { return toBytesReversed<dword>(b, v); }
}

#ifdef LIBUTIL_USE_GLOBAL_DATAUNIT
using byte = util::byte;
using hword = util::hword;
using word = util::word;
using dword = util::dword;

static constexpr byte BYTE_MAX = UINT8_MAX;
static constexpr hword HWORD_MAX = UINT16_MAX;
static constexpr word WORD_MAX = UINT32_MAX;
static constexpr dword DWORD_MAX = UINT64_MAX;
#endif
