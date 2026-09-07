#include "common.h"

extern char *reverseBytes(char *a0, u16 a1);

/* uint-to-decimal-string: writes digits LSB-first into buf, NUL-terminates, then
   reverses the buffer via reverseBytes to produce the final decimal string. */
char *uintToDecStr(u32 num, char *buf)
{
    s32 count = 0;

    do {
        u32 q = num / 10;
        count++;
        *buf = (num - q * 10) + '0';
        buf++;
        num = q;
    } while (num != 0);
    *buf = 0;

    return reverseBytes(buf - count, count);
}
