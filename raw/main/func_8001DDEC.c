#include "common.h"

extern u8 D_80408CF0[];

void *func_8001DDEC(void *arg0, s32 arg1, s32 arg2) {
    u8 *p;
    s32 i;

    p = arg0;
    p[1] = 0x81;
    *(s16 *)(p + 4) = 0x20;
    *(s16 *)(p + 6) = 0;
    p += 0xC;
    i = 0;
    do {
        p[1] = 0x38;
        *(s32 *)(p + 4) = 0x9CBCBC;
        *(s32 *)(p + 12) = 0x9CBCBC;
        *(s32 *)(p + 16) = 0x9CBCBC;
        *(s32 *)(p + 20) = 0x8C9C9C;
        p[10] = (s8)(arg1 / 2);
        p[11] = (s8)(arg2 / 2);
        *p = D_80408CF0[i];
        i += 1;
        p += 0x18;
    } while (i < 4);
    p[1] = 0x81;
    *(s16 *)(p + 4) = 0x20;
    *(s16 *)(p + 6) = 1;
    p[0] = 0x80;
    return p + 0xC;
}
