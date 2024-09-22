#pragma once

#include <cstdint>
#include <span>
#include <string>
#include <vector>

namespace base64
{
    extern const char digits[65];
    extern const int8_t map[256];

    bool isValid(const char *str, uint64_t str_size) noexcept;
    bool isValid(std::string_view str) noexcept;

    /**
     * @throw std::overflow_error if if there is an overflow
     */
    uint64_t sizeEncoded(std::span<const uint8_t> data);
    uint64_t sizeDecoded(std::string_view str) noexcept;

    /**
     * @throw std::length_error if not enough allocated length
     */
    void encode(const uint8_t *data, uint64_t data_size, char *str, uint64_t str_size);
    std::string encode(std::span<const uint8_t> data) noexcept;

    /**
     * @throw std::length_error if not enough allocated length
     * @throw std::logic_error if out of digits map
     * @throw std::logic_error if incorrect padding
     */
    void decode(const char *str, uint64_t str_size, uint8_t *data, uint64_t data_size);
    std::vector<uint8_t> decode(std::string_view str) noexcept;
}