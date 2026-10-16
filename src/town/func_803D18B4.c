/* Relink of matched town/func_8032EC84; every changed retail word is a paired relocation. */
#define townAppendString func_800188B4
#include "common.h"

/* Append the source string to the destination and return the destination start. */
u8 *func_800188B4(u8 *dst, u8 *src) {
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
