#include "common.h"
/* Writes decimal digits least significant first, pads to width, and null-terminates. */
char *func_8004E4C0(u32 value, s32 width, char *buf, s32 pad) {
    s32 char_count;
    u32 quotient_or_width;
    s32 digit_limit;
    register u32 quotient ASM_REG("$2");   /* MATCH pin: slus-diff */
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
            if (value == 0) break;
            char_count++;
            quotient = value / 10u;
            ASM_KEEP_NV(quotient);   /* MATCH pin: slus-diff */
            *buf++ = (char)((value - quotient * 10u) + '0');
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
