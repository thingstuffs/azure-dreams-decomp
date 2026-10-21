#include "common.h"
#include "engine/util.h"

/* Converts an unsigned integer to a NUL-terminated decimal string. */
char *uint_to_dec_str(u32 num, char *buf)
{
    s32 digit_count = 0;

    do {
        u32 quotient = num / 10;
        digit_count++;
        *buf = (num - quotient * 10) + '0';
        buf++;
        num = quotient;
    } while (num != 0);
    *buf = 0;

    return reverse_bytes(buf - digit_count, digit_count);
}
