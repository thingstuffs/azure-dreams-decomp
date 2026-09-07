#include "common.h"

extern u8 D_800A79F0[12];

void func_800A79C8(void *arg0, void *arg1, void *arg2) {
    *(void **)((s8 *)arg0 + 0x50) = D_800A79F0;
    *(s16 *)((s8 *)arg0 + 0x6C) = 0x16;
    *(u8 *)((s8 *)arg2 + 0x0E) = 0x80;
    *(u8 *)((s8 *)arg2 + 0x0D) = 0x80;
    *(u8 *)((s8 *)arg2 + 0x0C) = 0x80;
}
