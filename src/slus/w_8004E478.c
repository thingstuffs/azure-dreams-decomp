#include "common.h"

/* Reverses the first `len` bytes of `buf` in place; returns the original buf pointer. */
void *reverseBytes(u8 *buf, u16 len)
{
    u8 *orig = buf;
    u8 *end = orig + (len - 1);
    while (buf < end) {
        u8 t = *buf;
        u8 t2 = *end;
        *end = t;
        end--;
        *buf = t2;
        buf++;
    }
    return orig;
}
