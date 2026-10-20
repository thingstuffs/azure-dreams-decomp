#include "common.h"

/* Copy four bytes and return the advanced destination pointer. */
void *copy_four_text_bytes(u8 *src, u8 *dst) {
    *dst++ = *src++;
    *dst++ = *src++;
    *dst++ = *src++;
    *dst++ = *src++;
    return dst;
}
