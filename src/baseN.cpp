#include <algorithm>
#include <cmath>
#include <limits>
#include <stdexcept>

#include <basen/baseN.hpp>
#include <basen/Exception.hpp>

static constexpr auto log256 = std::log(256);

namespace baseN
{
    void digitsMap(const char *digits, uint8_t digits_size, uint8_t *map)
    {
        std::fill(map, map + 256, 255);
        for (uint8_t i = 0; i < digits_size; i++)
        {
            if (map[(uint8_t)digits[i]] != 255)
            {
                throw basen::Exception(basen::Exception::Code::ALPH_COLLISION);
            }
            map[(uint8_t)digits[i]] = i;
        }
    }
    bool isValid(const char *str, size_t str_size, const uint8_t *map) noexcept
    {
        return std::all_of(str, str + str_size, [map](char ch)
                           { return map[(uint8_t)ch] != 255; });
    }
    bool isValid(std::string_view str, const uint8_t *map) noexcept
    {
        return baseN::isValid(str.data(), str.size(), map);
    }
    size_t sizeEncoded(std::span<const uint8_t> data, uint8_t base)
    {
        if (base < 2 || base > 254)
        {
            throw basen::Exception(basen::Exception::Code::BASE);
        }
        std::span<const uint8_t> dv(std::find_if(data.begin(), data.end(), [](uint8_t item)
                                                 { return item != 0; }),
                                    data.end());
        if (dv.size() > std::numeric_limits<size_t>::max() / log256)
        {
            throw basen::Exception(basen::Exception::Code::OVERFLOW);
        }
        return dv.size() * log256 / std::log(base) + 1 + (data.size() - dv.size());
    }
    size_t sizeDecoded(std::string_view str, uint8_t base, const char *digits)
    {
        if (base < 2 || base > 254)
        {
            throw basen::Exception(basen::Exception::Code::BASE);
        }
        std::string_view sv(std::find_if(str.begin(), str.end(), [digits](uint8_t ch)
                                         { return ch != digits[0]; }),
                            str.end());
        return sv.size() * std::log(base) / log256 + 1 + (str.size() - sv.size());
    }
    size_t encode(const uint8_t *data, size_t data_size, char *str, size_t str_size, uint8_t base, const char *digits)
    {
        if (base < 2 || base > 254)
        {
            throw basen::Exception(basen::Exception::Code::BASE);
        }
        std::vector<uint8_t> dv(std::find_if(data, data + data_size, [](uint8_t item)
                                             { return item != 0; }),
                                data + data_size);
        std::span<char> sv(str, str_size);
        auto sv_it = sv.rbegin();
        auto dv_it = dv.begin();
        auto quo_it = dv.begin();
        auto quo_it_last = dv.end();

        if (dv.size() != 0)
        {
            uint16_t div = *dv_it++;
            while ((dv[0] > base || quo_it_last > dv.begin() + 1) && sv_it < sv.rend() - 1)
            {
                if (div < base)
                {
                    div <<= 8;
                    div += *dv_it++;
                }
                *quo_it++ = div / base;
                div %= base;
                while (dv_it < quo_it_last)
                {
                    div <<= 8;
                    div += *dv_it++;
                    *quo_it++ = div / base;
                    div %= base;
                }
                quo_it_last = quo_it;
                dv_it = dv.begin();
                quo_it = dv.begin();
                *sv_it++ = digits[div];
                div = *dv_it++;
            }
            *sv_it++ = digits[div];
        }
        for (size_t i = 0; i < data_size - dv.size() && sv_it < sv.rend(); i++)
        {
            *sv_it++ = digits[0];
        }
        return std::distance(sv_it, sv.rend());
    }
    std::string encode(std::span<const uint8_t> data, uint8_t base, const char *digits)
    {
        std::string str(baseN::sizeEncoded(data, base), ' ');
        size_t offset = baseN::encode(data.data(), data.size(), str.data(), str.size(), base, digits);
        str.erase(str.begin(), str.begin() + offset);
        return str;
    }
    size_t decode(const char *str, size_t str_size, uint8_t *data, size_t data_size, uint8_t base, const char *digits, const uint8_t *map)
    {
        if (base < 2 || base > 254)
        {
            throw basen::Exception(basen::Exception::Code::BASE);
        }
        std::string_view sv(std::find_if(str, str + str_size, [digits](char ch)
                                         { return ch != digits[0]; }),
                            str + str_size);
        if (!baseN::isValid(sv, map))
        {
            throw basen::Exception(basen::Exception::Code::OUT_OF_ALPH);
        }
        std::span<uint8_t> dv(data, data_size);
        auto sv_it = sv.begin();
        auto quo_it = dv.rbegin();
        auto quo_it_last = dv.rbegin();
        uint16_t div;

        if (sv.size() != 0)
        {
            quo_it_last++;
            *quo_it = map[(uint8_t)*sv_it++];
            while (sv_it < sv.end())
            {
                div = map[(uint8_t)*sv_it++];
                while (quo_it < quo_it_last && quo_it < dv.rend())
                {
                    div += *quo_it * base;
                    *quo_it++ = div;
                    div >>= 8;
                }
                if (div != 0 && quo_it < dv.rend())
                {
                    *quo_it++ = div;
                }
                quo_it_last = quo_it;
                quo_it = dv.rbegin();
            }
        }
        for (size_t i = 0; i < str_size - sv.size() && quo_it_last < dv.rend(); i++)
        {
            *quo_it_last++ = 0;
        }
        return std::distance(quo_it_last, dv.rend());
    }
    std::vector<uint8_t> decode(std::string_view str, uint8_t base, const char *digits, const uint8_t *map)
    {
        std::vector<uint8_t> data(baseN::sizeDecoded(str, base, digits));
        size_t offset = baseN::decode(str.data(), str.size(), data.data(), data.size(), base, digits, map);
        data.erase(data.begin(), data.begin() + offset);
        return data;
    }
}