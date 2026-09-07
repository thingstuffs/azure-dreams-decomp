#include "common.h"

extern u16 D_80083462[5];
s32 func_8009C93C(void *arg0, s32 arg1, s16 arg2, s32 arg3, s32 arg4);
s16 func_800A2B5C(void *arg0);
s32 func_800C7930(void *arg0, s32 arg1, s32 arg2, s32 arg3);

void func_8016BAE0(void *arg0, s32 arg1, s32 arg2, void *arg3) {
    *(u8 *)((s8 *)arg3 + 0x71) &= 0x7F;
    if (!(*D_80083462 & 0x2000) && ((func_800A2B5C(arg3) << 0x10) == 0)) {
        func_800C7930((s8 *)arg3 - 0x20, arg1, 8, 0x300);
        if ((func_800A2B5C(arg3) << 0x10) == 0) {
            *(s32 *)((s8 *)arg0 + 0x8C) = 0;
            *(s8 *)((s8 *)arg0 + 0x9A) = 0x11;
            *(s8 *)((s8 *)arg0 + 0x9B) = 0;
            *(u8 *)((s8 *)arg3 + 0x6D) = *(u8 *)((s8 *)arg3 + 0x6D) - 1;
            func_8009C93C(arg3, arg2, *(s16 *)((s8 *)arg3 + 0x2A), 1, 0);
            *(u8 *)((s8 *)arg3 + 0x84) = 0x80;
            *(u8 *)((s8 *)arg3 + 0x85) = 0x20;
        }
    }
}

