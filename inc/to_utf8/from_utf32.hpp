#pragma once
#ifndef PCH
    #include <algorithm>
    #include <cstdint>
#endif

namespace to_utf8
{
    template <typename T>
    T from_utf32(const char32_t character, T dest) noexcept
    {
        static constexpr std::array<uint32_t, 7> ranges {
            0x7F,      // 127
            0x7FF,     // 2047
            0xFFFF,    // 65535
            0x1FFFFF,  // 2097151
            0x3FFFFFF, // 67108863
        };

        auto index = std::distance(ranges.begin(), std::lower_bound(ranges.begin(), ranges.end(), character));
        switch (index)
        {
            case 0:
            {
                *dest++ = static_cast<uint8_t>(character & 0xFF);
                break;
            }
            case 1:
            {
                const auto trunc1 = character >> 6u;
                const auto trunc2 = character % 64u;
                uint8_t c1 = 192u, c2 = 128u;
                for (auto i = 6u, and_op = 1u; i != 0u; --i, and_op <<= 1)
                {
                    c1 |= trunc1 & and_op;
                    c2 |= trunc2 & and_op;
                }

                *dest++ = c1;
                *dest++ = c2;
                break;
            }
            case 2:
            {
                const auto trunc1 = character >> 6u;
                const auto trunc2 = character % 64u;
                const auto trunc3 = character >> 12u;
                uint8_t c1 = 224, c2 = 128, c3 = 128;
                for (auto i = 6u, and_op = 1; i != 0u; --i, and_op <<= 1)
                {
                    c1 |= trunc1 & and_op;
                    c2 |= trunc2 & and_op;
                    c3 |= trunc3 & and_op;
                }

                *dest++ = c1;
                *dest++ = c2;
                *dest++ = c3;
                break;
            }
            case 3:
            {
                const auto trunc1 = character >> 6u;
                const auto trunc2 = character % 64u;
                const auto trunc3 = character >> 12u;
                const auto trunc4 = character >> 18u;
                uint8_t c1 = 240, c2 = 128, c3 = 128, c4 = 128;
                for (auto i = 6u, and_op = 1u; i != 0u; --i, and_op <<= 1)
                {
                    c1 |= trunc1 & and_op;
                    c2 |= trunc2 & and_op;
                    c3 |= trunc3 & and_op;
                    c4 |= trunc4 & and_op;
                }

                *dest++ = c1;
                *dest++ = c2;
                *dest++ = c3;
                *dest++ = c4;
                break;
            }
            default:;
        }

        return dest;
    }
}
