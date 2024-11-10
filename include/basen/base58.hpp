#pragma once

#include <cstdint>
#include <span>
#include <string>
#include <vector>

namespace base58
{
    /**
     * @brief bitcoin alphabet
     */
    extern const char digits[59];
    extern const uint8_t map[256];

    /**
     * @return checks what contains only alphabet chars
     * @warning doesn't validate checksum, use decodeCheck instead
     */
    bool isValid(const char *str, size_t str_size) noexcept;
    /**
     * @param str string or string_view which you want to decode
     * @return checks what contains only alphabet chars
     * @warning doesn't validate checksum, use decodeCheck instead
     */
    bool isValid(std::string_view str) noexcept;

    /**
     * @param data vector or span of data which you want to encode
     * @return estimated size after encoding (for non-powers of two it is obviously larger)
     * @throw basen::Exception(OVERFLOW) from baseN::sizeEncoded
     */
    size_t sizeEncoded(std::span<const uint8_t> data);
    /**
     * @param str string or string_view which you want to decode
     * @return estimated size after decoding (for non-powers of two it is obviously larger)
     */
    size_t sizeDecoded(std::string_view str) noexcept;

    /**
     * @param data [in] pointer to data which you want encode
     * @param str [out] pointer to string for encoded data output
     * @return number of leading chars, which should be trimmed
     * @throw basen::Exception(OVERFLOW) from base58::sizeEncoded
     * @warning contain leading zeros, returns count of them
     */
    size_t encode(const uint8_t *data, size_t data_size, char *str, size_t str_size);
    /**
     * @param data vector or span of data which you want to encode
     * @return encoded string
     * @throw basen::Exception(OVERFLOW) from base58::sizeEncoded
     */
    std::string encode(std::span<const uint8_t> data);

    /**
     * @param str [in] pointer to string which you want decode
     * @param data [out] pointer to data for encoded string output
     * @return number of leading chars, which should be trimmed
     * @throw basen::Exception(OUT_OF_ALPH) from baseN::decode
     * @warning contain leading zeros, returns count of them
     */
    size_t decode(const char *str, size_t str_size, uint8_t *data, size_t data_size);
    /**
     * @param str string or string_view which you want to decode
     * @return decoded data
     * @throw basen::Exception(OUT_OF_ALPH) from baseN::decode
     */
    std::vector<uint8_t> decode(std::string_view str);

    /**
     * @param data vector or span of data which you want to encode
     * @return encoded string + 4 first bytes of double sha256
     * @throw basen::Exception(OVERFLOW) from base58::encode
     */
    std::string encodeCheck(std::span<const uint8_t> data);
    /**
     * @param str encoded string or string_view + 4 first bytes of double sha256
     * @return decoded data without 4 first bytes of double sha256
     * @throw basen::Exception(OUT_OF_ALPH) from base58::decode
     * @throw basen::Exception(PADDING) if str size < 4
     * @throw basen::Exception(CHECKSUM) if checksum incorrect
     */
    std::vector<uint8_t> decodeCheck(std::string_view str);
}