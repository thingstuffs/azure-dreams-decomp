#include "common.h"
/* Writes decimal digits least significant first, pads to width, and null-terminates. */
char *format_reversed_unsigned_decimal(u32 value, s32 width, char *buf, s32 pad) {
    s32 char_count;
    u32 quotient_or_width;
    s32 digit_limit;
    u32 quotient;
    char_count = 1;
    quotient_or_width = value / 10u;
    *buf = (char)((value - quotient_or_width * 10u) + '0');
    quotient_or_width = width & 0xFFFF;
    buf++;
    if (char_count < (s32)quotient_or_width) {
        digit_limit = quotient_or_width;
        do {
top:
            value = value / 10u;
            if (value == 0)
                break;
            char_count++;
            quotient = value / 10u;
            quotient_or_width = quotient << 2;
            quotient_or_width += quotient;
            quotient_or_width += quotient_or_width;
            quotient_or_width = value - quotient_or_width;
            quotient_or_width += '0';
            *buf++ = (char)quotient_or_width;
        } while (char_count < digit_limit);
        quotient_or_width = width & 0xFFFF;
        while (char_count < (s32)quotient_or_width) {
            *buf++ = (char)pad;
            char_count++;
        }
    }
    *buf = 0;
    return buf - (width & 0xFFFF);
}
