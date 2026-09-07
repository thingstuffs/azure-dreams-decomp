#include "common.h"

extern u8 D_800814D1[16];
extern u8 D_800814D1_read[16] __asm__("D_800814D1");

#define KEEP_POINTER(value) \
    __asm__ __volatile__("" : "=r"(value) : "0"(value))

s32 func_8003F270(void)
{
    u8 *p = &D_800814D1[0];
    u32 cur = D_800814D1_read[0];

    KEEP_POINTER(p);

    if (cur < p[-1]) {
        cur += 0x20;
    }

    return cur - p[-1];
}
