#include "common.h"

void *func_8001D7B0(u8 *a0) {
    s32 t0;
    s32 t1;
    s32 t2;
    void *ret;

    *(a0 + 1) = 0xB0;
    t0 = *(s32 *)0x80408CC4;
    *(s32 *)(a0 + 8) = t0;
    t1 = *(s32 *)0x80408CCC;
    t2 = *(s32 *)0x80408CC8;
    *(a0 + 1) = *(a0 + 1) | 2;
    *(s32 *)(a0 + 4) = t1;
    *(s32 *)(a0 + 0xC) = t2;
    a0 = a0 + 24;
    *(a0 + 1) = 0x81;
    *(s16 *)(a0 + 4) = 0x20;
    ret = a0 + 0xC;
    *(s16 *)(a0 + 6) = 0;
    *a0 = *a0 | 0x80;
    return ret;
}
