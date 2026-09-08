#include "common.h"

/* Copy four bytes and return the advanced destination pointer. */
void *func_80099254(u8 *src, u8 *dst) {
    *dst++ = *src++;
    *dst++ = *src++;
    *dst++ = *src++;
    *dst++ = *src++;
    return dst;
}
