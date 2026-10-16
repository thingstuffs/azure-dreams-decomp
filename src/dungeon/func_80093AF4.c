#include "common.h"

/* Copy four bytes and return the advanced destination pointer. */
void *dungeonCopyFourTextBytes(u8 *src, u8 *dst) {
    *dst++ = *src++;
    *dst++ = *src++;
    *dst++ = *src++;
    *dst++ = *src++;
    return dst;
}
