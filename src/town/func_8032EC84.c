#include "common.h"

/* Append the source string to the destination and return the destination start. */
u8 *func_80019484(u8 *dst, u8 *src) {
    u8 *dst_start = dst;

    while (*dst != 0) {
        dst++;
    }
    while (*src != 0) {
        *dst = *src;
        dst++;
        src++;
    }
    *dst = 0;
    return dst_start;
}
