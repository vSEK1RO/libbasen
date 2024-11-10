#pragma once

#include <cstdint>
#include <span>
#include <string>
#include <vector>

namespace hex
{
    /**
     * @brief lower case chars
     */
    extern const char digits[17];
    extern const uint8_t map[256];

    /**
     * @return checks what contains only alphabet chars
     */
    bool isValid(const char *str, size_t str_size) noexcept;
    /**
     * @param str string or string_view which you want to decode
     * @return checks what contains only alphabet chars
     */
    bool isValid(std::string_view str) noexcept;

    /**
     * @param data vector or span of data which you want to encode
     * @return exact size after encoding
     * @throw basen::Exception(OVERFLOW) if there is an overflow
     */
    size_t sizeEncoded(std::span<const uint8_t> data);
    /**
     * @param str string or string_view which you want to decode
     * @return exact size after decoding
     */
    size_t sizeDecoded(std::string_view str) noexcept;

    /**
     * @param data [in] pointer to data which you want encode
     * @param str [out] pointer to string for encoded data output
     * @throw basen::Exception(OVERFLOW) from hex::sizeEncoded
     * @throw basen::Exception(LENGTH) if not enough allocated length
     */
    void encode(const uint8_t *data, size_t data_size, char *str, size_t str_size);
    /**
     * @param data vector or span of data which you want to encode
     * @return encoded string
     * @throw basen::Exception(OVERFLOW) from hex::sizeEncoded
     * @throw basen::Exception(LENGTH) if not enough allocated length
     */
    std::string encode(std::span<const uint8_t> data);

    /**
     * @param str [in] pointer to string which you want decode
     * @param data [out] pointer to data for encoded string output
     * @throw basen::Exception(LENGTH) if not enough allocated length
     * @throw basen::Exception(OUT_OF_ALPH) if out of digits map
     * @throw basen::Exception(PADDING) if str_size %2 != 0 (isn't hex)
     */
    void decode(const char *str, size_t str_size, uint8_t *data, size_t data_size);
    /**
     * @param str string or string_view which you want to decode
     * @throw basen::Exception(LENGTH) if not enough allocated length
     * @throw basen::Exception(OUT_OF_ALPH) if out of digits map
     * @throw basen::Exception(PADDING) if str_size %2 != 0 (isn't hex)
     */
    std::vector<uint8_t> decode(std::string_view str);
}