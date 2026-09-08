#include "common.h"

extern char *reverseBytes(char *a0, u16 a1);

/* Converts an unsigned integer to a NUL-terminated decimal string. */
char *uintToDecStr(u32 num, char *buf)
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

    return reverseBytes(buf - digit_count, digit_count);
}
