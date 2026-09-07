#include "common.h"

extern void bzero(void *dst, s32 size);
extern s32 D_800D1648[];

u32 func_800B2280(s32 *arg0, s32 arg1, s32 arg2) {
    u8 used[256];
    s32 base;
    s32 i;

    bzero(used, arg2);
    base = D_800D1648[arg1];

    while (*arg0 != 0) {
        used[(u32)(*arg0++ - base) >> 2] = 1;
    }

    i = 0;
    if (used[0] != 0) {
        do {
            i++;
        } while (used[i] != 0);
    }

    return base + (i * 4);
}
