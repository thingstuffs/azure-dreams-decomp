#include "common.h"

extern u8 *D_800DD71C[];

void *func_800992A8(s32 arg0, u8 *arg1) {
    u8 *dst;

    dst = arg1;
    if (arg0 != 0) {
        u8 *src;

        src = D_800DD71C[0];
        if (arg0 <= 0) {
            src += 2;
        }

        *dst++ = *src++;
        *dst++ = *src++;
    }
    return dst;
}
