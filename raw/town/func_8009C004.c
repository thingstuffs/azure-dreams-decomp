#include "common.h"

extern u8 D_80082660[];
extern u8 D_800D05E0[];

void func_80099764(void *arg0) {
    u8 *base;

    *(void **)((u8 *)arg0 + 0x44) = D_800D05E0;
    *(s32 *)((u8 *)arg0 + 0x40) = 1;
    base = D_80082660;
    *(void **)(base + 0xC) = (u8 *)arg0 - 0x20;
    base[8] = 0;
}
