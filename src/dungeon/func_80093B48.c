#include "common.h"

extern u8 *D_800DD71C[];

/* Append two bytes selected by the sign of the value, or nothing for zero. */
void *func_800992A8(s32 value, u8 *buffer) {
    u8 *dst;

    dst = buffer;
    if (value != 0) {
        u8 *src;

        src = D_800DD71C[0];
        if (value <= 0) {
            src += 2;
        }

        *dst++ = *src++;
        *dst++ = *src++;
    }
    return dst;
}
