#include "common.h"

#include "common.h"
#include "engine/movie.h"
#include "engine/town.h"

/* Writes value as fullwidth decimal digits and returns a pointer to the null terminator. */
u8 *format_unsigned_double_byte_decimal(u32 value, u8 *out)
{
    u8 digits[16];
    u8 *digit = digits;
    s32 digit_count = 0;

    do {
        *digit = value % 10;
        digit_count++;
        value /= 10;
        digit++;
    } while (value != 0);

    digit = reverse_town_movie_buffer_bytes(digits, digit_count);
    do {
        *out++ = 0x82;
        *out++ = *digit++ + 0x4F;
        digit_count--;
    } while (digit_count > 0);
    *out = 0;
    return out;
}
