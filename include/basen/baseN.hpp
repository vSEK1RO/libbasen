#pragma once

#include <cstdint>
#include <span>
#include <string>
#include <vector>

namespace baseN
{
    /**
     * @param digits [in] alphabet of encoding
     * @param map [out] uint8_t[256] array, where at an index equal to the value of the symbol is the index of this symbol in the digits array. 255 if there is no symbol
     * @return map of alphabet of encoding
     * @throw basen::Exception(ALPH_COLLISION) if alphabet contain same chars
     */
    void digitsMap(const char *digits, uint8_t digits_size, uint8_t *map);
    /**
     * @param map map of alphabet of encoding, which is returned by baseN::digitsMap
     * @return checks what contains only alphabet chars
     */
    bool isValid(const char *str, size_t str_size, const uint8_t *map) noexcept;
    /**
     * @param str string or string_view which you want to decode
     * @param map map of alphabet of encoding, which is returned by baseN::digitsMap
     * @return checks what contains only alphabet chars
     */
    bool isValid(std::string_view str, const uint8_t *map) noexcept;

    /**
     * @param data vector or span of data which you want to encode
     * @param base radix of encoding from [2 to 254]
     * @return estimated size after encoding (obviously larger)
     * @throw basen::Exception(BASE) if base < 2 || base > 254
     */
    size_t sizeEncoded(std::span<const uint8_t> data, uint8_t base);
    /**
     * @param str string or string_view which you want to decode
     * @param base radix of encoding from [2 to 254]
     * @param digits alphabet of encoding
     * @return estimated size after decoding (obviously larger)
     * @throw basen::Exception(BASE) if base < 2 || base > 254
     * @throw basen::Exception(OVERFLOW) if if there is an overflow
     */
    size_t sizeDecoded(std::string_view str, uint8_t base, const char *digits);

    /**
     * @param data [in] pointer to data which you want encode
     * @param str [out] pointer to string for encoded data output
     * @param base radix of encoding from [2 to 254]
     * @param digits alphabet of encoding
     * @return number of leading chars, which should be trimmed
     * @throw basen::Exception(BASE) if base < 2 || base > 254
     * @warning contain leading zeros, returns count of them
     */
    size_t encode(const uint8_t *data, size_t data_size, char *str, size_t str_size, uint8_t base, const char *digits);
    /**
     * @param data vector or span of data which you want to encode
     * @param base radix of encoding from [2 to 254]
     * @param digits alphabet of encoding
     * @return encoded string
     * @throw basen::Exception(BASE) if base < 2 || base > 254
     */
    std::string encode(std::span<const uint8_t> data, uint8_t base, const char *digits);

    /**
     * @param str [in] pointer to string which you want decode
     * @param data [out] pointer to data for encoded string output
     * @param base radix of encoding from [2 to 254]
     * @param digits alphabet of encoding
     * @param map map of alphabet of encoding, which is returned by baseN::digitsMap
     * @return number of leading chars, which should be trimmed
     * @throw basen::Exception(BASE) if base < 2 || base > 254
     * @throw basen::Exception(OUT_OF_ALPH) if out of alphabet
     * @warning contain leading zeros, returns count of them
     */
    size_t decode(const char *str, size_t str_size, uint8_t *data, size_t data_size, uint8_t base, const char *digits, const uint8_t *map);
    /**
     * @param str string or string_view which you want to decode
     * @param base radix of encoding from [2 to 254]
     * @param digits alphabet of encoding
     * @param map map of alphabet of encoding, which is returned by baseN::digitsMap
     * @return decoded data
     * @throw basen::Exception(BASE) if base < 2 || base > 254
     * @throw basen::Exception(OUT_OF_ALPH) if out of alphabet
     */
    std::vector<uint8_t> decode(std::string_view str, uint8_t base, const char *digits, const uint8_t *map);
}